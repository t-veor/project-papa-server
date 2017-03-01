# Project Papa Server

This is the server counterpart to the Project Papa project.

## Usage

To use, clone the repository and use cmake to build.

```
git clone https://github.com/project-papa/project-papa-server --recursive
cd project-papa-server
mkdir build && cd build
cmake ..
make
```

This will create a build directory and a `server` executable in the build
directory.

## Connecting to the server

By default, the server is listening to `ws://localhost:9612`. You can currently
send it two messages of the forms

```json
{ "command": "stop-all-jobs" }
```

```json
{ "command": "run-code", "code": "# ruby code here" }
```

The server will also relay messages from the server and broadcast them to any
connected sockets. See the [Sonic Pi
API](https://github.com/samaaron/sonic-pi/wiki/Sonic-Pi-Internals----GUI-Ruby-API)
for an explanation of the different messages. Here are some examples of the
formats of the messages: (TODO: replace this with a proper specification,
probably)

```json
{
  "message_type": "log/info",
  "message": {
    "style": 0,
    "body": "Studio: Pausing SuperCollider audio server"
  }
}
```

```json
{
  "message_type": "log/multi_message",
  "message": {
    "job_id": 6,
    "thread_name": "",
    "runtime": "22.8462",
    "messages": [
      {
        "type": 5,
        "body": "synced :heartbeat (Run 6)"
      },
      {
        "type": 0,
        "body": "sample \"/usr/share/sonic-pi/samples\",\n           \"bd_haus.flac\", {amp: 0.6, lpf: 80}"
      },
      {
        "type": 4,
        "body": "cue :base"
      },
      {
        "type": 6,
        "body": "sync :heartbeat"
      }
    ]
  }
}
```

```json
{
  "message_type": "error",
  "message": {
    "job_id": 2,
    "desc": "[buffer eval, line 1]\nThread death!\n undefined local variable or method `asdf&#39; for Runtime:SonicPiLang",
    "backtrace": "eval:1:in `block (2 levels) in __spider_eval&#39;\n/usr/lib/sonic-pi/server/sonicpi/lib/sonicpi/lang/core.rb:3564:in `block in in_thread&#39;",
    "line": 1
  }
}
```

```json
{
  "message_type": "/syntax_error",
  "message": {
    "job_id": 3,
    "desc": "[buffer eval, line 1] \n syntax error, unexpected keyword_do_block",
    "error_line": "if do\n",
    "line": 1,
    "line_num_s": "1"
  }
}
```

## Subscribing to oscilloscope data

To subscribe to oscilloscope data, send a JSON object structured like this,
with the scopes array containing the required scopes.

```json
{
  "command": "subscribe",
  "scopes": [1, 6, 12]
}
```

The server will then start broadcasting messages in this format to all
connected sockets.

```json
{
  "message_type": "scope/amp",
  "data": {
    "1": 0.64,
    "6": 0.23,
    "12": 0.41,
  }  
}
```

Sending another subscribe command will replace the scopes in the broadcasts
with the scopes specified. To get the server to stop sending messages, simply
send a subscribe message with an empty scopes array.

## Contributing

### Setting up your workspace

To get ready to make contributions, you'll need to have your own version of
this repository. We use [Git](https://git-scm.com/) for version control, and
we're hosting it on GitHub.

This guide will only have a high-level overview of Git. There are plenty of
guides you can follow online to get a better idea. You can also ask someone
else on the Papa team for help.

Fork this repository from your account by clicking on the "Fork" button at the
top right

With Git installed, clone your fork, and configure the repository

```
git clone https://github.com/<<YOUR USERNAME>>/project-papa-server --recursive
cd project-papa-server
git remote add upstream https://github.com/project-papa/project-papa-server
```

You will be making changes to your local fork, pushing them, then opening pull
requests against the canonical copy (upstream).

If changes have been made to the canonical copy, you can pull them down at any
time:

```
git checkout master
git pull upstream master
```

### Making Changes

To make changes, you want to check out a new branch

```
git checkout -b BRANCH_NAME
```

Then, make changes to your code. Add the feature you plan to add. Please write
new tests, and then run them to make sure nothing is broken.

```
cd build
cmake .. && make test
```

Then you want to commit your changes, and push them to your fork

```
git add . # Add all changed files
git commit -m "MY MESSAGE" # Make a commit with a message
git push origin HEAD # Push the newly committed branch to your fork
```

After this, you'll be able to make a pull request by going to the repository
home page (this page) and clicking the big "Pull Request" button that should
appear

### Code Review

Your changes will need to be approved by another member of the team. Nominate
one when you're making a pull request.

Smaller changes are easier to review than larger ones, so it is wise to keep
pull requests small. It will also help you as a developer to make focused
changes.
