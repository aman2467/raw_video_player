/* ==========================================================================
 * @file    : raw_video_player.c
 *
 * @description : This file contains the code of raw video player.
 *
 * @author  : Aman Kumar (2015)
 *
 * @copyright   : The code contained herein is licensed under the GNU General
 *				Public License. You may obtain a copy of the GNU General
 *				Public License Version 2 or later at the following locations:
 *              http://www.opensource.org/licenses/gpl-license.html
 *              http://www.gnu.org/copyleft/gpl.html
 * ========================================================================*/

#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BPP 2

int get_SDL_pixfmt(int fmt)
{
	switch(fmt) {
		case 1:
			return SDL_PIXELFORMAT_YUY2;
		case 2:
			return SDL_PIXELFORMAT_YV12;
		case 3:
			return SDL_PIXELFORMAT_IYUV;
		case 4:
			return SDL_PIXELFORMAT_UYVY;
		case 5:
			return SDL_PIXELFORMAT_YVYU;
		case 6:
			return SDL_PIXELFORMAT_RGB565;
		case 7:
			return SDL_PIXELFORMAT_BGR565;
		case 8:
			return SDL_PIXELFORMAT_RGB332;
		default:
			return -1;
	}
}

int validPath(char *path)
{
	struct stat st;

	if (stat(path, &st) < 0)
		return 0;

	return 1;
}

/****************************************************************************
 * @function : This is the video player main function. It plays recorded video
 *             using simple DirectMedia Layer(SDL2).
 *
 * @arg  : command line arg
 * @return     : success/failure
 * *************************************************************************/
int main(int argc, char **argv )
{
	SDL_Window *win = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *texture = NULL;
	char resolution[50] = {0};
	int format = 0, bpp = BPP;
	int width, height;
	FILE *fp;
	char *frame = NULL;
	int fps = 0, delay = 0;

	if(argc != 2) {
		printf("Usage: %s <video_file.raw>\n", argv[0]);
		exit(0);
	}

	if(!validPath(argv[1])) {
		printf("Invalid File\n");
		return -1;
	}

	printf("Supported Format::\n");
	printf("\t1 : YUY2\n");
	printf("\t2 : YV12\n");
	printf("\t3 : IYUV\n");
	printf("\t4 : UYVY\n");
	printf("\t5 : YVYU\n");
	printf("\t6 : RGB565\n");
	printf("\t7 : BGR565\n");
	printf("\t8 : RGB332\n");
	printf("Enter the video format : ");
	if(scanf(" %d", &format) < 0) {
		return -1;
	}

	format = get_SDL_pixfmt(format);
	if(format < 0) {
		printf("Error : Invalid Format\n");
		return -1;
	}

	printf("Pixel depth(No. of bytes per pixel) : ");
	if(scanf(" %d", &bpp) < 0) {
		return -1;
	}

	printf("Width of the video : ");
	if(scanf(" %d", &width) < 0) {
		return -1;
	}

	printf("Height of the video : ");
	if(scanf(" %d", &height) < 0) {
		return -1;
	}

	printf("Frame Per Second(FPS) : ");
	if(scanf(" %d", &fps) < 0) {
		return -1;
	}

	delay = 1000000/(fps+15);
	snprintf(resolution, 50, "Raw Video Player : %dx%d", width, height);
	frame = (char *)calloc(1, width*height*bpp);
	if(!frame) {
		printf("Failed to allocate frame\n");
		return -1;
	}

	SDL_Init(SDL_INIT_VIDEO);
	win = SDL_CreateWindow(resolution, 
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, 
			width, 
			height, 
			SDL_WINDOW_RESIZABLE);

	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	texture = SDL_CreateTexture(renderer,
			format,
			SDL_TEXTUREACCESS_STREAMING,
			width,
			height);

	fp = fopen(argv[1],"rb");
	if(fp == NULL) {
		perror("fopen");
		return -1;
	}

	while (1) {
		SDL_Event e;

		if(fread(frame, 1, width*height*bpp, fp) < width*height*bpp) {
			fclose(fp);
			fp = fopen(argv[1], "rb");
			if(fp == NULL) {
				perror("fopen");
				return -1;
			}
			if(fread(frame, 1, width*height*bpp, fp) < width*height*bpp);
		}
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				break;
			}
		}
		SDL_UpdateTexture(texture,
				0,
				frame,
				width*bpp);
		usleep(delay);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	free(frame);
	fclose(fp);
	SDL_Quit();

	return 0;
}
