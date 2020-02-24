include $(TOPDIR)/rules.mk

PKG_NAME:=edge-utils
PKG_VERSION:=4.3
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/edge-utils
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=SAGE EDGE Utilities
  DEPENDS:=+bluez-utils +raspi-gpio +cc2564-firmware +whiptail
endef

define Build/Compile

endef

define Package/edge-utils/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) ./files/btuart $(1)/usr/bin
	$(INSTALL_BIN) ./files/edge-config $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/btuart.init $(1)/etc/init.d/btuart
endef

$(eval $(call BuildPackage,edge-utils))

