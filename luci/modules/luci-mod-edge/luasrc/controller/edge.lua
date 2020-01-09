-- Copyright 2020 Simon Crawley <simon.crawley@gotosage.com>
-- Licensed to the public under the Apache License 2.0.

module("luci.controller.edge", package.seeall)

function index()
	if not nixio.fs.access("/etc/config/edge") then
		return
	end
	
	entry({"admin", "edge", "config"}, cbi("edge/config"), _("Configuration")).dependent=true
end