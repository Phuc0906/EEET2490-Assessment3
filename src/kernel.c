#include "./uart/uart0.h"
#include "./mailbox/mbox.h"
#include "./display/framebf.h"

// letter should has length 10
void drawLetter(int letter[]) {
    int startX = 5;
    int startY = 5;
    int letterSpace = 15;

    for (int i = 0; i < 10; i++) {
        for (int k = 8; k >= 0; k--) {
            // uart_sendc('*');
            // uart_sendc((letterA[i] >> k) & 0xF);
            // uart_sendc('*');
            if ((letter[i] >> k) & 0b1) {
                uart_sendc('1');
                drawRectARGB32(startX, startY, startX + 5, startY + 5, 0x00ffffff, 1);  
            }else {
                uart_sendc('0');
            }
            startX += 5;
        }
        uart_sendc('\n');
        startX = 5;
        startY += 5;
    }
}

void displayImg(int count, int imgIdx) {
    int x = 0;
    int y = 0;

    while (count < 1024 * 1024) {
        if (count > 1024 * 1024 - 1) {
            break;
        }
        drawPixelARGB32(y, x, pixels[imgIdx][count]);
        count++;
        y++;
        if (y >= 1024) {
            y = 1;
            x++;
        }
    }
}

void main()
{
    // intitialize UART
    uart_init();

    // say hello

    uart_puts("\n\nHello World!\n");
    // Initialize frame buffer
    framebf_init();

    // printImg();

    

    // base on letterboard. Each letter has lenght of 9 * 10 
    // each row represent a binary to display (if 1 => a square of 5x5 pixels will be drawn)
    // each letter has 9 bits
    static const int letterA[10] = {
        0b001111110,
        0b001111111,
        0b000000011,
        0b000000011,
        0b011111111,
        0b111111111,
        0b110000011,
        0b110000011,
        0b111111111,
        0b011111111
    };

    drawLetter(letterA);


    
    
    int count = 0;
    int lastCount = 0;
    int moving = 0;
    int imgIdx = 0;
    int lastImgIdx = 0;
    // displayImg(count, imgIdx);

    while (1)
    {
        // read each char
        char c = uart_getc();
        
        // if (c == 'w') {
        //     moving += 5;
        //     count = 1024 * moving;
        // }else if (c == 's') {
        //     moving -= 5;
        //     count = 1024 * moving;
        // }else if (c == 'd') {
        //     if (imgIdx < 2) {
        //         imgIdx++;
        //     }
        // }else if (c == 'a') {
        //     if (imgIdx > 0) {
        //         imgIdx--;
        //     }
        // }

        // if (imgIdx != lastImgIdx) {
        //     lastImgIdx = imgIdx;
        //     count = 0;
        //     displayImg(count, imgIdx);
        // }

        // if (count != lastCount) {
        //     displayImg(count, imgIdx);
        //     lastCount = count;
        // }
    }
}
