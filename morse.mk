#########
# morse #                                                
#########
MORSE_VERSION = 1.0
MORSE_SITE = $(TOPDIR)/../app_morse/morse_src_mak
MORSE_SITE_METHOD = local
MORSE_DEPENDENCIES = libgpiod
define MORSE_BUILD_CMDS
	$(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(@D)
endef
define MORSE_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/morse $(TARGET_DIR)/usr/bin
endef
MORSELICENSE = Proprietary
$(eval $(generic-package))