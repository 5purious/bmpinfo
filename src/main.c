#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <bmp.h>

// 2022 Ian Moffett

struct BMP bmp;

int main(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf("<==== Usage ====>\n");
            printf("%s file.bmp\n", argv[0]);
            return 0;
        } else if (access(argv[i], F_OK) != 0) {
            printf("bmpinfo: I couldn't find that file!\n");
            return -1;
        } else {
            FILE* fp = fopen(argv[i], "r");

            if (!(fp)) {
                printf("bmpinfo: Error opening file!\n");
            }

            fseek(fp, 0, SEEK_END);
            size_t sz = ftell(fp);
            fseek(fp, 0, SEEK_SET);

            bmp.pixel_data = malloc(sz);

            fread(&bmp, (sizeof(bmp) / 2)+25, sizeof(char), fp);

            // Verify magic bytes.
            if ((bmp.header.signature & 0xFF) != 'B' || (bmp.header.signature >> 8) != 'M') {
                printf("bmpinfo: Not a valid BMP, magic bytes invalid!\n");
                free(bmp.pixel_data);
                fclose(fp);
                return -1;
            }

            printf("File size is %d bytes.\n", bmp.header.file_size);
            printf("Image width is %d pixels.\n", bmp.info_header.width);
            printf("Image height is %d pixels.\n", bmp.info_header.height);
                
            free(bmp.pixel_data);
            fclose(fp);
        }
    }

    return 0;
}
