include $(TOPDIR)/rules.mk

PKG_NAME:=onebox-utils
PKG_VERSION:=1
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=RS9113 Onebox Utilities
  DEPENDS:=+hub-ctrl 
endef

define Build/Compile

endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) 	$(1)/usr/bin
	$(INSTALL_BIN) 	./files/usr/bin/* $(1)/usr/bin
endef

$(eval $(call BuildPackage,$(PKG_NAME)))

