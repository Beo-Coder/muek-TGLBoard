//
// Created by leo on 22.05.24.
//

#include "flash_controller.h"
#include <hardware/sync.h>






// Initiation of flash content


FlashItem data0{4, 1};
FlashItem data1{4, 2};
FlashItem *flashContent[FLASH_ITEM];





FlashController::FlashController() {
    // Load flash content in the array
    flashContent[0] = &(data0);
    flashContent[1] = &(data1);

    resetBuffer();

}


void FlashController::resetBuffer() {
    for(unsigned char & i : bufferData){
        i = 0x00;
    }

}


void FlashController::eraseAllSectors() {
    // Disable IRQs
    uint32_t ints = save_and_disable_interrupts();

    // Erase all sectors
    flash_range_erase((uint32_t)FLASH_WRITE_OFFSET_BEGIN, FLASH_SECTOR_SIZE*NUMBER_OF_SECTORS);

    // Restore IRQs
    restore_interrupts(ints);
}



uint32_t FlashController::findNextFreeSector() {
    uint8_t *address = nullptr;

    for(uint32_t page=0; page<(FLASH_SECTOR_SIZE*NUMBER_OF_SECTORS)/FLASH_PAGE_SIZE; page++){
        uint8_t *localAddress = (uint8_t *) FLASH_READ_OFFSET_BEGIN+(page*FLASH_PAGE_SIZE);
        // We found a free page
        if(*localAddress == 0xFF){
            // If enough pages are still free in this block of memory
            if(((FLASH_SECTOR_SIZE*NUMBER_OF_SECTORS)/FLASH_PAGE_SIZE) - page >= NUMBER_OF_PAGES){
                address = localAddress;
            }
            break;
        }
    }
    // If flash is full
    if(address == nullptr){
        eraseAllSectors();
        address = (uint8_t *) FLASH_READ_OFFSET_BEGIN;
    }

    return (uint32_t) address;
}

uint32_t FlashController::findLastDataSector() {
    uint8_t *address = nullptr;
    uint8_t numberOfPagesFound = 0;

    for(int page=((FLASH_SECTOR_SIZE*NUMBER_OF_SECTORS)/FLASH_PAGE_SIZE)-1; page>=0; page--){
        uint8_t *localAddress = (uint8_t *) FLASH_READ_OFFSET_BEGIN+(page*FLASH_PAGE_SIZE);

        // If page has data written to it
        if(*localAddress == FIRST_BYTE_PATTERN_WRITE){
            numberOfPagesFound++;

            // Go x pages before that to retrieve out full data set
            if(numberOfPagesFound == NUMBER_OF_PAGES){
                address = localAddress;
                break;
            }
        }
    }
    // If flash is clear
    if(address == nullptr){
        return 0;
    }

    return (uint32_t) address;
}


bool FlashController::writeData(const uint8_t accessKey, const uint8_t *data) {

    // Get address to write to and subtract the XIP BASE, so that we get the offset to XIP_BASE
    uint32_t startAddress = findNextFreeSector() - XIP_BASE;


    for(int pageIndex = 0; pageIndex<NUMBER_OF_PAGES; pageIndex++){
        prepareBufferData(pageIndex);
        if(!loadDataInBuffer(accessKey, data, pageIndex)) return false;

        // Disable all IRQs
        uint32_t ints = save_and_disable_interrupts();

        // Program the flash
        flash_range_program(startAddress+(FLASH_PAGE_SIZE*pageIndex), bufferData, FLASH_PAGE_SIZE);

        // Restore IRQs
        restore_interrupts(ints);

    }

    return true;

}

uint8_t *FlashController::readData(const uint8_t accessKey) {

    auto *data = (uint8_t *) findLastDataSector();
    if(data == nullptr)return nullptr;
    // Add offset for buffer
    data += findBufferOffsetWriteData(accessKey);
    // Add offset for first byte
    data += 1;

    return data;
}

uint32_t FlashController::findBufferOffsetWriteData(const uint8_t accessKey) {

    uint32_t offset = 0;
    for(int i=0; i<FLASH_ITEM; i++){
        const FlashItem *p = flashContent[i];
        if(p != nullptr){
            if(p->accessKey == accessKey){
                return offset;
            }
            offset += p->sizeInBytes;
        }
    }
    return UINT32_MAX;
}

void FlashController::prepareBufferData(uint8_t pageIndex) {

    auto *data = (uint8_t *) findLastDataSector();
    // If flash is completely clear, use the beginning
    if(data == nullptr){
        data = (uint8_t*) FLASH_READ_OFFSET_BEGIN;
    }
    data = data + FLASH_PAGE_SIZE*pageIndex;

    // Load write buffer data with old flash data
    for(uint32_t i=0; i<FLASH_PAGE_SIZE; i++){
        bufferData[i] = *(data + i);
    }

    bufferData[0] = FIRST_BYTE_PATTERN_WRITE;

}

bool FlashController::loadDataInBuffer(const uint8_t accessKey, const uint8_t *data, const uint8_t pageIndex) {
    uint32_t offset = findBufferOffsetWriteData(accessKey);
    if(offset == UINT32_MAX)return false;

    // is offset in the current page
    if(offset >= FLASH_PAGE_SIZE*pageIndex && offset <= FLASH_PAGE_SIZE*(pageIndex+1)){
        // Get offset for buffer
        offset = offset % FLASH_PAGE_SIZE;
        // Add offset of +1 for first byte
        offset += 1;

        // Get Length for data
        uint32_t dataLength = getFlashContentDataLength(accessKey);
        if(dataLength == 0)return false;

        // Load new data in buffer
        for(uint32_t i= 0; i<dataLength; i++){
            bufferData[offset+i] = data[i];
        }

    }
    return true;


}

uint32_t FlashController::getFlashContentDataLength(uint8_t accessKey) {
    for(uint32_t i=0; i<FLASH_ITEM; i++){
        const FlashItem *p = flashContent[i];
        if(p != nullptr){
            if(p->accessKey == accessKey){
                return p->sizeInBytes;
            }
        }
    }
    return 0;
}

void FlashController::eraseAllData() {
    eraseAllSectors();

}





