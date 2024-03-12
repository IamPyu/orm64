local sockets = require("sockets")

local sfd = sockets.new()
sockets.bind(sfd)
sockets.listen(sfd)
