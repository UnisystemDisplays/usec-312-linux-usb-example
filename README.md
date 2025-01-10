OVERVIEW
--------
![img1](/Docs/img_1.png)

*usec-312-linux-usb-example* is a ready to use app example and fast, free and fully portable C library for linux-based computers and [*Unisystem USEC/USEM*](https://unisystem.com/pl/produkt/wyswietlacze-e-papierowe/wyswietlacze/usec312sblusn-elektroniczny-wyswietlacz-papierowy-od-unisystem-co) e-paper controllers equipped with 31.2-inch display.

LIBRARY API
-----------

*usec_dev.c* and *usec_dev.h* files provide minimal set of optimized functions for performing common tasks like e-paper module intialization, uploading new content and updating display:

```c
usec_ctx *
usec_init                    (void);

void
usec_deinit                  (usec_ctx  *ctx);

uint8_t
usec_get_temp                (usec_ctx  *ctx,
                              uint8_t   *temp_val);

uint8_t
usec_get_vcom                (usec_ctx  *ctx,
                              uint16_t  *vcom_val);

uint8_t
usec_img_upload              (usec_ctx  *ctx,
                              uint8_t   *img_data,
                              size_t     img_size);

uint8_t
usec_img_update              (usec_ctx  *ctx,
                              uint8_t    update_mode,
                              uint8_t    update_wait);
```

MINIMAL USAGE EXAMPLE
---------------------

Thanks of highly-optimized API, fully working example needs only few lines of code:

```c
int
main()
{
  usec_ctx *ctx;
  uint8_t status;

  /* initialize controller */
  ctx = usec_init();
  if (ctx == NULL)
    {
      printf ("[error] cannot initialize e-ink controller\n\r");
      return;
    }

  usec_img_upload(...)
  usec_img_update(...)

  /* cleanup */
  usec_deinit(ctx);

  return EXIT_SUCCESS;
}
```

APP COMPILATION
---------------

[1] Clone *usec-312-linux-usb-example* repository:

```
cd ~
git clone https://github.com/UnisystemDisplays/usec-312-linux-usb-example.git
```

[2] [optional] Install provided *99-UniEPDC312BWN0.rules* udev file - thanks of that e-paper controller always will be visible in system as */dev/eink_usec_312BWN0_** device: 

```
cd usec-312-linux-usb-example
sudo cp 99-UniEPDC312BWN0.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules && sudo udevadm trigger
```

[3] Build and run demo application:

```
make
sudo ./usec-312-linux-usb-example
```

GETTING HELP
------------

Please contact Unisystem support - [*<lukasz.skalski@unisystem.com>*](lukasz.skalski@unisystem.com) or [*<jacek.marcinkowski@unisystem.com>*](jacek.marcinkowski@unisystem.com)

LICENSE
-------

See *LICENSE.txt* file for details.
