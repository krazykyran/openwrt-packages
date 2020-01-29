include $(TOPDIR)/rules.mk

PKG_NAME:=raspi-gpio
PKG_VERSION:=1
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/RPi-Distro/raspi-gpio.git
PKG_SOURCE_DATE:=2019-12-05
PKG_SOURCE_VERSION:=4edfde183ff3ac9ed66cdc015ae25e45f3a5502d

include $(INCLUDE_DIR)/package.mk

# Package definition; instructs on how and where our package will appear in the overall configuration menu ('make menuconfig')
define Package/$(PKG_NAME)
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Raspberry Pi GPIO configuration tool
  URL:=https://github.com/RPi-Distro/raspi-gpio
endef

# Package description; a more verbose description on what our package does
define Package/$(PKG_NAME)/description
  The Raspberry Pi GPIO configuration tool.
endef

# Package configuration; use defaults, with linux headers
define Build/Configure
  $(call Build/Configure/Default,--with-linux-headers=$(LINUX_DIR))
endef

# Package build instructions; invoke the target-specific compiler to first compile the source file, and then to link the file into the final executable
define Build/Compile
	$(TARGET_CC) $(TARGET_CFLAGS) -o $(PKG_BUILD_DIR)/raspi-gpio.o -c $(PKG_BUILD_DIR)/raspi-gpio.c
	$(TARGET_CC) $(TARGET_LDFLAGS) -o $(PKG_BUILD_DIR)/$1 $(PKG_BUILD_DIR)/raspi-gpio.o
endef

# Package install instructions; create a directory inside the package to hold our executable, and then copy the executable we built previously into the folder
define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(PKG_NAME) $(1)/usr/bin
endef

# This command is always the last, it uses the definitions and variables we give above in order to get the job done
$(eval $(call BuildPackage,$(PKG_NAME)))

