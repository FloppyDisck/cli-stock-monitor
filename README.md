# CLI Stock Monitor
A simple program that monitors stocks given by a text file.

## Alpaca API setup

The program will pick APCA_API_SECRET_KEY and APCA_API_KEY_API from your enviroment variables.

## Building and Running Binaries

You can use Bazel automagically set everything up!

Build and run:
```
$ bazel run //src:main
```

Build then run:
```
$ bazel build //src:main
$ ./bazel-bin/src/main
```
