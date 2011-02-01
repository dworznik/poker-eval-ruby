spec = Gem::Specification.new do |s|
  s.name = 'poker-eval'
  s.version = '0.0.2'
  s.summary = "Ruby interface for pokereval."
  s.description = %{Interface for pokereval}
  s.files = Dir['lib/**/*.rb'] + Dir['ext/**/*']
  s.require_paths << 'lib'
  s.require_paths << 'ext'
  s.require_paths << 'ext/lib'
  s.extensions << 'ext/poker_eval/extconf.rb'
  s.extensions << 'ext/poker_eval_api/extconf.rb'
  s.has_rdoc = false
  s.author = "Patryk Dworznik"
  s.email = "dwuziu@bzium.net"
  s.homepage = "http://bzium.net"
end
