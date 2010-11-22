`tar --strip-components 1 -xkzvf sources/poker-eval-138.0.tar.gz -C poker-eval`

spec = Gem::Specification.new do |s|
  s.name = 'pokereval'
  s.version = '0.0.1'
  s.summary = "Ruby interface for pokereval."
  s.description = %{Interface for pokereval}
  s.files = Dir['lib/**/*.rb'] + Dir['ext/**/*'] + Dir['poker-eval/**/*']
  s.require_paths << 'lib'
  s.require_paths << 'ext'
  s.extensions << 'poker-eval/extconf.rb'
  s.extensions << 'ext/extconf.rb'
  s.has_rdoc = false
  s.author = "Patryk Dworznik"
  s.email = "dwuziu@bzium.net"
  s.homepage = "http://bzium.net"
end
