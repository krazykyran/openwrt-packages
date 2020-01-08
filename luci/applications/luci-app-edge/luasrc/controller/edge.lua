-- Copyright 2020 Simon Crawley <simon.crawley@gotosage.com>
-- Licensed to the public under the Apache License 2.0.

module("luci.controller.edge", package.seeall)

function index()
	if not nixio.fs.access("/etc/config/edge") then
		return
	end
	
	local page
	
	page = entry({"admin", "system", "edge"}, cbi("edge"), _("EDGE Configuration"))
	page.dependent = true
end