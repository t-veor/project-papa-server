{
  (sleep 2s; ./server) &
  ./app/server/native/osx/ruby/bin/ruby ./app/server/bin/sonic-pi-server.rb;
}
