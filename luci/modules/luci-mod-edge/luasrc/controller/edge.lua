-- Copyright 2020 Simon Crawley <simon.crawley@gotosage.com>
-- Licensed to the public under the Apache License 2.0.

module("luci.controller.edge", package.seeall)

function index()	
	entry({"admin", "edge"}, firstchild(), "EDGE", 60).dependent=false
	entry({"admin", "edge", "config"}, cbi("edge/config"), "Configuration")
end