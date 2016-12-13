# jdate
The persian jalali calendar date tool for GNU command line.
 
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
To convert gregorian date to persian jalali date issue the following:
```
$ ./jdate -g 1395-09-20
```
To convert persian jalali date to gregorian date issue the following:
```
$ ./jdate -j 2016-12-20
```
To compair two different persian jalali date issue the following:
```
$ ./jdate -c 1395-09-10:1396-08-06
```
NOTE: above command will return the bigger date.

To change the format of the output issue the following:
```
$ ./jdate -f 'Y-m-d' 
```
