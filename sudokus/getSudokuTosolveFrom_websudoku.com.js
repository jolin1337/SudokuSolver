/*
 * This is a JavaScript Scratchpad.
 *
 * Enter some JavaScript, then Right Click or choose from the Execute Menu:
 * 1. Run to evaluate the selected text (Ctrl+R),
 * 2. Inspect to bring up an Object Inspector on the result (Ctrl+I), or,
 * 3. Display to insert the result in a comment after the selection. (Ctrl+L)
 */
var sudokuPuzzle = 'EMPTYSQUARE=0\n';
var sep = "---------------------\n";
for(var i=0;i<9;i++){
    if(i%3 == 0 && i != 0)
        sudokuPuzzle += sep;
    for(var j = 0;j<9;j++){
        var num = document.getElementById(('f'+i)+j);
        if(j%3== 0 && j != 0)
            sudokuPuzzle += '| ';
        if(num.value)
            sudokuPuzzle += num.value + ' ';
        else
            sudokuPuzzle += '0 ';
    }
    sudokuPuzzle += '\n';
}
alert(sudokuPuzzle);