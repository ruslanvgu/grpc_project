    #!/bin/bash

    # команды из документации
    # protoc -I ../../protos --grpc_out=. --plugin=protoc-gen-grpc=which grpc_cpp_plugin ../../protos/route_guide.proto
    # protoc -I ../../protos --cpp_out=. ../../protos/route_guide.proto

    echo "Run script $0"

    # Установите путь для утилиты protoc и плагина protoc-gen-grpc
    PROTOC_PATH="/home/ruslanvgu/.local/bin/protoc"
    GRPC_PLUGIN_PATH="/home/ruslanvgu/.local/bin/grpc_cpp_plugin"
    #Дирректория где находится протофайлы
    PROTO_FILES_DIR="."
    #Дирректория куда будут сгенерированы полуенные файлы
    CPP_DIR_OUT="."
    # Установите путь к прото файлу
    PROTO_FILES_PATH="*.proto"
    # Компиляция прото файла с генерацией gRPC кода
    $PROTOC_PATH   \
    --proto_path=$PROTO_FILES_DIR \
    --grpc_out=$CPP_DIR_OUT   \
    --plugin=protoc-gen-grpc=$GRPC_PLUGIN_PATH \
    $PROTO_FILES_PATH

    $PROTOC_PATH   \
    --proto_path=$PROTO_FILES_DIR \
    --cpp_out=$CPP_DIR_OUT \
    $PROTO_FILES_PATH