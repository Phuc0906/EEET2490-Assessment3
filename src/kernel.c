#include "./uart/uart0.h"
#include "./mailbox/mbox.h"

void main()
{
    // intitialize UART
    uart_init();
    // say hello

    uart_puts("\n\nHello World!\n");
    // Initialize frame buffer
    framebf_init();
    // Draw something on the screen
    drawRectARGB32(100, 100, 400, 400, 0x00AA0000, 1); // RED
    drawRectARGB32(150, 150, 400, 400, 0x0000BB00, 1); // GREEN
    drawRectARGB32(200, 200, 400, 400, 0x000000CC, 1); // BLUE
    drawRectARGB32(250, 250, 400, 400, 0x00FFFF00, 1); // YELLOW
    drawPixelARGB32(500, 900, 0x00FF0000);             // RED

    printImg();
    // for (int i = 0; i < 200; i++) {
    //     drawPixelARGB32(200 + i, 900, 0x00AA0000);
    // }

    // for (int y = 0; y <= 200; y++) {
    //     for (int x = 0; x <= 200; x++)
    //     {
    //         drawPixelARGB32(500 + x, 500 + y, 0x00AA0000);
    //     }
    // }

    

    while (1)
    {
        // read each char
        char c = uart_getc();
        // send back
        uart_sendc(c);
    }
}
