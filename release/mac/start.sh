{
  (sleep 2s; ./server/server) &
  ./server/app/server/native/osx/ruby/bin/ruby ./server/app/server/bin/sonic-pi-server.rb;
}
