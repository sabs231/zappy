require './client/command'

class Zappy

  def initialize(socket, team)
    @socket = socket
    @team = team
    @alive = true
    @manager = Command.new(team)
    @cmds = Array.new
  end

  def run

    Thread.new {
      while @alive == true
	str = @socket.get
	if (str == nil)
	  @alive = false
        else
          puts str
	end
      end
    }

    Thread.new {
      while @alive == true
	  @socket.send gets
	end
    }
    while @alive == true
      for cmd in @cmds
        @manager.manageCommand cmd
      end
      @cmds.clear
    end

    puts "You are dead"

  end

end
