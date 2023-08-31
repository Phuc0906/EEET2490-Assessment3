#include "./uart/uart0.h"
#include "./mailbox/mbox.h"
#include "./display/framebf.h"

void displayImg(int count) {
    int x = 0;
    int y = 0;

    while (count < 1024 * 1024) {
        if (count > 1024 * 1024 - 1) {
            break;
        }
        drawPixelARGB32(y, x, pixels[count]);
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

    // drawRectARGB32(0, 0, 400, 400, 0x00AA0000, 1);
    
    int count = 0;
    int lastCount = 0;
    int moving = 0;
    displayImg(count);

    while (1)
    {
        // read each char
        char c = uart_getc();
        
        if (c == 'w') {
            moving += 5;
            count = 1024 * moving;
        }else if (c == 's') {
            moving -= 5;
            count = 1024 * moving;
        }

        if (count != lastCount) {
            displayImg(count);
            lastCount = count;
        }
    }
}
