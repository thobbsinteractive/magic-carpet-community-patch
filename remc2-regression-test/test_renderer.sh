
REMC2_EXECUTABLE=./remc2

test_level() {
    level=$1
    echo "Testing renderer in level $level"
    ${REMC2_EXECUTABLE} --test_renderers --set_level $level --config_file_path ./renderer-config.ini
    
    if [ ${PIPESTATUS[0]} -eq 0 ]; then
        echo "test level $level ok"
    else
        echo "test level $level failed"
    fi
}

for i in `seq 0 24`; do
    test_level $i
done
