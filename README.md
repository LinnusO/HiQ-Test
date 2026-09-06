## Building

Requires `g++` with C++17 support.

```sh
make            # build the app
make all        # same as above
```

## Running

```sh
./RobotApp      # reads commands from input.txt
```

## Testing

```sh
make run-tests  # build and run all unit tests
```

Or build and run individually:

```sh
make RobotAppTest && ./RobotAppTest
make CommandParserTest && ./CommandParserTest
```
