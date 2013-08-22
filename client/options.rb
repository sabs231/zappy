require 'optparse'

def manageopt (options)
  options[:host] = "localhost"

  optparse = OptionParser.new do |opts|

    opts.on("-h", "--host HOSTNAME", "Optionnal Host Name") do |h|
      options[:host] = h
    end

    opts.on("-n", "--name TEAMNAME", "Mandatory Team Name") do |t|
      options[:team] = t
    end

    opts.on("-p", "--port PORT", Numeric, "Mandatory Port") do |p|
      options[:port] = p
    end

  end

  begin
    optparse.parse!

  rescue Exception => e
    puts e.message
    puts "Usage: -n teamname -p port [-h host]"
    exit
  end

  if options[:team].nil? || options[:port].nil?
    puts "Usage: -n teamname -p port [-h host]"
    exit
  end
end
