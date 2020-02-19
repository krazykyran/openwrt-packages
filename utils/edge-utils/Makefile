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
	$(INSTALL_DIR) 	$(1)/usr/bin
	$(INSTALL_BIN) 	./files/usr/bin/* $(1)/usr/bin
endef

$(eval $(call BuildPackage,edge-utils))

