include $(TOPDIR)/rules.mk

PKG_NAME:=ubertooth
PKG_VERSION:=2018-12-R1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_VERSION).zip
PKG_SOURCE_URL:=https://github.com/greatscottgadgets/ubertooth/archive/
PKG_HASH:=624c4c2248981d67c53fc609f2659772f9e7075e7f5d2a53371cb9b2e2442326
PKG_BUILD_DEPENDS:=libbtbb

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/$(PKG_NAME)
	SECTION:=utils
	CATEGORY:=Utilities
	DEPENDS:=+libbtbb +libusb-1.0 +bluez-libs
	TITLE:=Project Ubertooth
endef

define Package/$(PKG_NAME)/description
	Project Ubertooth is an open source wireless development platform suitable
	for Bluetooth experimentation. Ubertooth ships with a capable BLE (Bluetooth Smart)
	sniffer and can sniff some data from Basic Rate (BR) Bluetooth Classic connections.
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/usr/include
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
endef

$(eval $(call BuildPackage,$(PKG_NAME)))

