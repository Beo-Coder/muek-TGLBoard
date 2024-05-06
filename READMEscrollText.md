# Scroll Text Library

### Library to display scroll text on the matrix



# Usage
## General use
### Initialize
`ScrollText scrollText(<matrixOutput>, <frame>);`
- **matrixOutput**: Address of the MatrixOutput object (see example)
- **frame**: Address of the Color frame\[8\]\[16\] object (see example)


<br/>

### Set colors
`scrollText.setColor(<textColor>, <backgroundColor>);`

- **textColor**: Address of the color for the text.
- **backgroundColor**: Address of the color for the background.


<br/>

### Set text
`scrollText.setText(<text>);`

- **text**: Address of the text stored as a string.

See [decoding table](#decoding-table)

<br/>

### Shift text
`scrollText.shiftText();`

This command only shifts the text.
It does not display the text onto the matrix.
Use [refresh](#refresh-shift--display) instead or `matrixOutput.sendData();` after this command.

<br/>

### Refresh (shift + display)
`scrollText.refresh();`

This command shifts the text one place and displays it to the matrix.

<br/>

# Decoding Table

`String text = "Hello World %H";`

(input -> output(on display))

## Normal letters
A -> A  
B -> B  
...  
y -> y  
z -> z  

0 -> 0  
...  
9 -> 9

*space* -> *space* (5 pixel)    

( -> (  
) -> )  
\[ -> \[  
\] -> \]  
{ -> {  
} -> }  
< -> <  
\> -> \>

. -> .  
, -> ,  
_ -> _    <br>
\- -> \-  
? -> ?  
! -> !  
: -> :  
; -> ;


## Normal character (with `%` in fort (`%A` -> Ä))

A -> Ä  
a -> ä  
...  
ü -> ü  

1 -> *space* (1 pixel)  
2 -> *space* (2 pixel)  
3 -> *space* (3 pixel)  
4 -> *space* (4 pixel)  

l -> *vertical line* (1 pixel)  
| -> *vertical line* (1 pixel) (same as l)  

( -> ( (another design)  
) -> ) (another design)  

H -> *Heart symbol*  
S -> *Smiley face*  