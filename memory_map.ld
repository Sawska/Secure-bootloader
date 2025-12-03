MEMORY 
{
boot (rx)   : ORIGIN = 0x00000000, LENGTH = 0x00004000
app  (rx)   : ORIGIN = 0x00004000, LENGTH = 0x0003C000
ram  (rwx) : ORIGIN = 0x20000000, LENGTH = 0x00008000
}


__boot_start__ = ORIGIN(boot);
__boot_size__ = LENGTH(boot);
__app_start__ = ORIGIN(app);
__app_size__ = LENGTH(app);