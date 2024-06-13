//
// Created by leo on 22.05.24.
//

#ifndef TGL_BOARD_FLASH_CONTROLLER_FLASH_CONTROLLER_H
#define TGL_BOARD_FLASH_CONTROLLER_FLASH_CONTROLLER_H

#ifdef ARDUINO
#include <Arduino.h>
#else
#include "pico/stdlib.h"
#endif
#include <hardware/flash.h>


/*
 * Some explanations:
 *
 * Writing only flips bits to 0. We can only write one whole page (256 bytes).
 * Erasing only turns a whole sector to 1 (4096 bytes).
 * Each erase-cycle wears out the flash.
 *
 * Writing new data:
 * We read the data from the beginning a find the fist page, which is still erased (all 1).
 * We write to that sector.
 * If we don't find a sector, we erase the sector.
 *
 * Reading:
 * We will read until we find a page that does not have a specific pattern.
 */

/*
 * We will use 5 whole sectors (4096 * 5 = 20480 bytes) (we have more than enough to spare).
 * This will give us 80 page writes before we need to erase.
 *
 * We will only accept data, which is defined in this file.
 * The first byte of each sector we write will have a specific pattern.
 */

// Number of individual variables/data to store in the flash
#define FLASH_ITEM 3

// !!!!DO NOT CHANGE UNLESS YOU KNOW WHAT YOU ARE DOING!!!!

// Pattern for the first byte we write (so that we can easily detect free sectors)
#define FIRST_BYTE_PATTERN_WRITE 0x55

// Number of 4096 byte sectors we need to store our information/ we want to spare on erase-cycles.
// Should be double of needed sectors (e.g., you need 1 sector, it should be at least 2).
#define NUMBER_OF_SECTORS 5

// Number of 256 byte pages we need to store our information. Shouldn't be greater than 16 or everything will explode
#define NUMBER_OF_PAGES 1

// Flash region is at the end of the flash; Offset from XIP_BASE (Address to write)
#define FLASH_WRITE_OFFSET_BEGIN (PICO_FLASH_SIZE_BYTES-(FLASH_SECTOR_SIZE*NUMBER_OF_SECTORS))

// Offset from address 0x00 to read with pointers
#define FLASH_READ_OFFSET_BEGIN (XIP_BASE+FLASH_WRITE_OFFSET_BEGIN)


struct FlashItem{

    uint8_t sizeInBytes;
    uint8_t accessKey;
};






// Initiation of flash content

inline FlashItem highScoreDinoGame{4, 1};
inline FlashItem highScoreTetris{4, 2};
inline FlashItem globalBrightnessFlash{4, 3};
inline FlashItem *flashContent[] = {&highScoreDinoGame, &highScoreTetris, &globalBrightnessFlash};




class FlashController {

    uint8_t bufferData[FLASH_PAGE_SIZE];

    void resetBuffer();

    static uint32_t findBufferOffsetWriteData(uint8_t accessKey);
    uint32_t getFlashContentDataLength(uint8_t accessKey);
    void prepareBufferData(uint8_t pageIndex);
    bool loadDataInBuffer(uint8_t accessKey, const uint8_t* data, uint8_t pageIndex);


    static void eraseAllSectors();

    static void eraseFirstSectors();
    static void eraseLastSector();

    // Returns address WITH XIP_BASE
    static uint32_t findNextFreeSector();

    // Returns address WITH XIP_BASE
    static uint32_t findLastDataSector();



public:
    FlashController();

    /**
     * Erases all data from flash.
     * Only use if you know what you are doing
     */
    static void eraseAllData();

    /**
     * Writes data to flash. Size of that data is already defined.
     * @param accessKey Key for that specific flash data
     * @param data Data to write to flash. Size is fixed (application dependent)
     * @return true if successful
     */
    bool writeData(uint8_t accessKey, const uint8_t* data);

    /**
     * Reads data from the flash. Size of that data is already defined.
     * @param accessKey Key for that specific flash data
     * @return start address of data. nullptr if not found.
     */
    static uint8_t* readData(uint8_t accessKey);


};


#endif //TGL_BOARD_FLASH_CONTROLLER_FLASH_CONTROLLER_H

