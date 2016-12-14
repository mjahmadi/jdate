# jdate
The persian jalali calendar date tool for GNU command line.
Still needs some improvement and bug fix...

```
Display persian date in jalali calendar command line tool.
Usage: ./jdate [OPTION]... [+FORMAT]
  -h   --help          Display this usage information and exit.
  -f   --format        Formats output with the given pattern.
  -p   --no-pad        Won't pad numeric fields with zero.
  -j   --to-jalali     Converts given gregorian date to persian jalali date.
  -g   --to-gregorian  Converts given persian jalali date to gregorian date.
  -c   --compare       Will compare two different persian jalali date.
                       this option returns the bigger date. [YYYY-MM-DD:YYYY-MM-DD]
       --version       Output version information and exit.
```
## make

```
$ ./build.sh
```

## install

```
$ cp ./jdate /usr/bin/jdate
```

## usage
To get current persian jalali date issue the following:
```
$ ./jdate 
```

To convert persian jalali date to gregorian date issue the following:
```
$ ./jdate -g '1395-09-20'
```

To convert gregorian date to persian jalali date issue the following:
```
$ ./jdate -j '2016-12-20'
```

To compare two different persian jalali date issue the following:

[NOTE: The below command will return the bigger date]
```
$ ./jdate -c '1395-09-10:1396-08-06'
```

To change the format of the output issue the following:
```
$ ./jdate -f 'Y-m-d'
```

Report bugs to mohammad.j.ahmadi@gmail.com
Project home page: <https://github.com/MJAhmadi/jdate>
