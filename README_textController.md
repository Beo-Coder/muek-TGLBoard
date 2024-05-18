# Textcontroller Library

### Library the multiple text controllers to display different kinds of text in the matrix


# Overview
There are three different kinds of controllers. 
Scroll text, static text and tiny text.  
- **Scroll text**:
  The text is as high as the matrix and scroll from right to left
  (or from left to right) and start at the beginning if it reaches the end. 
  It is basically an endless loop of the same text.
- **Static text**: The text scrolls from right to left, but when it reaches the end it scrolls back to the beginning.
- **Tiny text**: 
  Same as static text, but only on half the size of the matrix. 
  The matrix is split in an upper and lower part.
  Each part can be controlled individual.

# Usage
## General use 
### Initialize
`ScrollText textController(<matrixOutput>, <frame>);`  
`StaticText textController(<matrixOutput>, <frame>);`  
`TinyText textController(<matrixOutput>, <frame>);`
- **matrixOutput**: Address of the MatrixOutput object (see example)
- **frame**: Address of the Color frame\[8\]\[16\] object (see example)


<br/>

### Set colors (only scroll and static text)
`textController.setColor(<textColor>, <backgroundColor>);`

- **textColor**: Address of the color for the text.
- **backgroundColor**: Address of the color for the background.

<br/>

### Set colors (only tiny text)
`textController.setColor(<upperTextColor>, <lowerTextColor>, <backgroundColor>);`

- **upperTextColor**: Address of the color for the text in the upper half.
- **lowerTextColor**: Address of the color for the text in the lower half.
- **backgroundColor**: Address of the color for the background


<br/>

### Set text (All controllers)
`textController.setText(<text>);`

- **text**: Address of the text stored as `std::string`.


<br/>

### Set text individual (tiny text only)
`textController.setUpperText(<text>);`  
`textController.setLowerText(<text>);`

- **text**: Address of the text stored as `std::string`.  
Sets the text individual for the upper/lower half.


See [decoding table](#decoding-table)

<br/>


### Refresh (shift + send to matrix) (All controllers)
`textController.refresh();`

This command shifts the text one place and displays it to the matrix.
Or display the static text.

<br/>

### Create and Load frame (shift + load frame) (All controllers)
`textController.createAndLoadFrame();`

This command creates the frame and loads it in to the buffer, so that it can be send as the next frame.  
You need to send the frame manually
(`matrix.sendData()`).

<br/>

### Set left/right shift (only scroll text)
`textController.setMode(<leftShift>);`

- **leftShift**: `bool`.
  If `true` text is shifted from right to left. 
  If `false` from left to right.
  Default is `true`

<br/>

# Decoding Table

`String text = "Hello World %H";`

(input -> output(on display))

## Normal Font (scroll and static text)
### Normal letters
`A` -> `A`  
`B` -> `B`  
...  
`y` -> `y`  
`z` -> `z`  

`0` -> `0`  
...  
`9` -> `9`

*space* -> *space* (5 pixel)    

`(` -> `(`  
`)` -> `)`  
`[` -> `[`  
`]` -> `]`  
`{` -> `{`  
`}` -> `}`  
`<` -> `<`  
`>` -> `>`

`.` -> `.`  
`,` -> `,`  
`_` -> `_`  
`-` -> `-`  

`?` -> `?`  
`!` -> `!`  
`:` -> `:`  
`;` -> `;`



### Special character (with `%` in front (`%A` -> `Ä`))

`A` -> `Ä`  
`a` -> `ä`  
...  
`ü` -> `ü`  

`1` -> *space* (1 pixel)  
`2` -> *space* (2 pixel)  
`3` -> *space* (3 pixel)  
`4` -> *space* (4 pixel)  

`l` -> *vertical line* (1 pixel)  
`|` -> *vertical line* (1 pixel) (same as l)  

`(` -> `(` (another design)  
`)` -> `)` (another design)  

`H` -> *Heart symbol*  
`S` -> *Smiley face*  


<br/>


## Tiny Font (tiny text)
### Normal letters
`A` -> `A`  
`B` -> `B`  
...  
`y` -> `A`  
`z` -> `Z`

There is no difference between small and capital letters.

`0` -> `0`  
...  
`9` -> `9`

*space* -> *space* (3 pixel)

`(` -> `(`  
`)` -> `)`  
`[` -> `[`  
`]` -> `]`   

`.` -> `.`  
`,` -> `,`  
`_` -> `_`  
`-` -> `-`

`?` -> `?`  
`!` -> `!`  
`:` -> `:`  
`;` -> `;`

`/` -> `/`  
`\ ` -> `\ `



### Special character (with `%` in front)



`1` -> *space* (1 pixel)  
`2` -> *space* (2 pixel)

`l` -> *vertical line* (1 pixel)  
`|` -> *vertical line* (1 pixel) (same as l)

`n` -> special char to indicate the line break if `text.setText(<text>);` is used.  
For example:
`Hello%nWorld` would become  
`Hello` (upper half)  
`World` (lower half)  