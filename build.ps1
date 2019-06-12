if (Test-Path ./bin/_$args.exe) {
    Remove-Item ./bin/_$args.exe
}

g++ ./src/$args.cpp -g -o ./bin/_$args.exe -Wall

if (Test-Path ./bin/_$args.exe) {
    & ./bin/_$args.exe
    $if=Read-Host "Debug(input '1')? "
    if($if -eq "1") {
        gdb.exe ./bin/_$args.exe
    }
}
else {
    "Build failed. Error."
}