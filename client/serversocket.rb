require 'socket'

class ServerSocket

  def close
    if @active == true
      @socket.close
    end
  end

  def initialize(options)  
    begin

      @socket = TCPSocket.new options[:host], options[:port]
      @active = true

    rescue Exception => e
      puts "Error from init connection:"
      puts e.message
      @active = false

    end
  end 

  def send(str)
    @socket.puts str
  end

  def get
    @socket.gets
  end

  def active
    @active
  end

end
