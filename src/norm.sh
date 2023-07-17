#!/bin/sh

# norminette $1

c_formatter_42 < $1 > $1.norm
rm $1; mv $1.norm $1
