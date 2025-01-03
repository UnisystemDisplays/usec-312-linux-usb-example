#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include "usec_dev.h"

/* stb_image */
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/* definitions */
#define DEMO_OK     0
#define DEMO_ERR    1

/* prototypes */
static uint8_t screen_cleanup (usec_ctx *ctx);
static uint8_t demo_image_fullscreen (usec_ctx *ctx, const char *img_path);

/******************************************************************************/

/*
 * main()
 */
int
main (void)
{
  usec_ctx *ctx;
  uint8_t status;
  uint8_t usec_temp;
  uint16_t usec_vcom;

  /* initialize controller */
  ctx = usec_init();
  if (ctx == NULL)
    {
      printf ("[error] cannot initialize e-ink controller\n\r");
      return EXIT_FAILURE;
    }

  /* read temperature value */
  status = usec_get_temp (ctx, &usec_temp);
  if (status != USEC_DEV_OK)
    {
      printf ("[error] cannot read temperature value\n\r");

      usec_deinit (ctx);
      return EXIT_FAILURE;
    }
  printf ("[status] screen temperature: %d [degC]\n\r", usec_temp);

  /* read vcom value */
  status = usec_get_vcom (ctx, &usec_vcom);
  if (status != USEC_DEV_OK)
    {
      printf ("[error] cannot read VCOM value\n\r");

      usec_deinit (ctx);
      return EXIT_FAILURE;
    }
  printf ("[status] screen VCOM: -%.2f [V]\n\r", (float) usec_vcom / 1000);

  /* cleanup screen - fullscreen update with UPDATE_MODE_INIT mode */
  screen_cleanup (ctx);

  /* fullscreen updates with UPDATE_MODE_GC16 mode */
  demo_image_fullscreen (ctx, "images/img_1.png");
  demo_image_fullscreen (ctx, "images/img_2.png");
  demo_image_fullscreen (ctx, "images/img_3.png");

  /* screen cleanup */
  sleep (2);
  screen_cleanup (ctx);

  /* cleanup */
  usec_deinit (ctx);
  ctx = NULL;

  return EXIT_SUCCESS;
}

/******************************************************************************/

/*
 * screen_cleanup()
 */
static uint8_t
screen_cleanup (usec_ctx *ctx)
{
  return usec_img_update (ctx, UPDATE_MODE_INIT, 0);
}

/******************************************************************************/

/*
 * demo_image_fullscreen()
 */
static uint8_t
demo_image_fullscreen (usec_ctx    *ctx,
                       const char  *img_path)
{
  uint8_t *img_data;
  uint8_t status;
  int img_res_x, img_res_y, img_ch_num;

  /* load BMP image - convert to grayscale (1 channel) */
  img_data = stbi_load (img_path, &img_res_x, &img_res_y, (int*)&img_ch_num, 1);
  if (img_data == NULL)
    {
      printf ("[error] cannot load '%s' image\n\r", img_path);
      return DEMO_ERR;
    }

  /* show image info */
  printf ("[demo] input image resolution: %dx%d\n\r", img_res_x, img_res_y);

  /* upload and display image */
  printf ("[demo] uploading '%s' image\n\r", img_path);
  status = usec_img_upload (ctx, img_data, img_res_x * img_res_y * 1);
  if (status != USEC_DEV_OK)
    {
      printf ("[error] cannot upload '%s' image\n\r", img_path);
      stbi_image_free (img_data);
      return DEMO_ERR;
    }

  /* fullscreen update with UPDATE_MODE_GC16 */
  printf ("[demo] displaying '%s' image\n\r", img_path);
  status = usec_img_update (ctx, UPDATE_MODE_GC16, 0);
  if (status != USEC_DEV_OK)
    {
      printf ("[error] cannot display '%s' image\n\r", img_path);
      stbi_image_free (img_data);
      return DEMO_ERR;
    }

  /* cleanup */
  stbi_image_free (img_data);
  return DEMO_OK;
}

/******************************************************************************/
