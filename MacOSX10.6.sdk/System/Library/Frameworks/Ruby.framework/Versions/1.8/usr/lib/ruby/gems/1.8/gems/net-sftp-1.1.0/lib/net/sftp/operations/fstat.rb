#--
# =============================================================================
# Copyright (c) 2004, Jamis Buck (jamis@37signals.com)
# All rights reserved.
#
# This source file is distributed as part of the Net::SFTP Secure FTP Client
# library for Ruby. This file (and the library as a whole) may be used only as
# allowed by either the BSD license, or the Ruby license (or, by association
# with the Ruby license, the GPL). See the "doc" subdirectory of the Net::SFTP
# distribution for the texts of these licenses.
# -----------------------------------------------------------------------------
# net-sftp website: http://net-ssh.rubyforge.org/sftp
# project website : http://rubyforge.org/projects/net-ssh
# =============================================================================
#++

require 'net/sftp/operations/abstract'

module Net ; module SFTP ; module Operations

  # The implementation of the +fstat+ operation.
  class Fstat < Abstract

    # Ask the server for the attributes of the file/directory represented by
    # the given handle.
    def perform( handle )
      @driver.fstat( nil, handle )
    end

  end

end ; end ; end
