#!/usr/bin/env ruby

require './client/options'
require './client/serversocket'
require './client/zappy'

begin

  options = {}
  manageopt(options)

  ssocket = ServerSocket.new(options)

  if ssocket.active == true
    puts "Connection established"

    if (ssocket.get == "BIENVENUE\n")
      ssocket.send options[:team]
      puts "Number of client remaining: " + ssocket.get
      puts "Map size: " + ssocket.get
    end

    zappy = Zappy.new(ssocket, options[:team])
    zappy.run

    ssocket.close
  end

rescue Exception => e
  puts "Client: server unreachable"
  exit

end
