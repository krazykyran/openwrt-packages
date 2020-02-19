include $(TOPDIR)/rules.mk

PKG_NAME:=ubertooth
PKG_VERSION:=2018-12-R1

PKG_BUILD_DIR=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/greatscottgadgets/ubertooth.git
PKG_SOURCE_VERSION:=2018-12-R1
PKG_BUILD_DEPENDS:=libbtbb bluez

CMAKE_BINARY_SUBDIR:=host
CMAKE_SOURCE_SUBDIR:=host
CMAKE_OPTIONS:=
	-DLIBBTBB_INCLUDE_DIR=$(STAGING_DIR)/usr/include \
	-DLIBBLUETOOTH_INCLUDE_DIR=$(STAGING_DIR)/usr/include

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/ubertooth
	SECTION:=utils
	CATEGORY:=Utilities
	DEPENDS:=+libbtbb +libusb-1.0 +bluez-libs +ubertooth-firmware
	TITLE:=Project Ubertooth
endef

define Package/ubertooth/description
	Project Ubertooth is an open source wireless development platform suitable
	for Bluetooth experimentation. Ubertooth ships with a capable BLE (Bluetooth Smart)
	sniffer and can sniff some data from Basic Rate (BR) Bluetooth Classic connections.
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/libubertooth.so.1.1 $(1)/usr/lib/
	$(LN) libubertooth.so.1.1 $(1)/usr/lib/libubertooth.so.1
	$(LN) libubertooth.so.1 $(1)/usr/lib/libubertooth.so
endef

define Package/ubertooth/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/ubertooth-util $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/ubertooth-dfu $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/ubertooth-rx $(1)/usr/bin/
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/libubertooth.so.1.1 $(1)/usr/lib/
	$(LN) libubertooth.so.1.1 $(1)/usr/lib/libubertooth.so.1
	$(LN) libubertooth.so.1 $(1)/usr/lib/libubertooth.so
endef

$(eval $(call BuildPackage,ubertooth))
