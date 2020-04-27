#!/bin/bash

cat $"TheRepublic.txt" | sed "s/Socrates/Moisés/g" | \
                    sed "s/Thrasymachus/Omar/g" | \
                    sed "s/Greece/library/g" | \
                    sed "s/Piraeus/Sunday/g" | \
                    sed "s/Polemarchus/1:00pm/g" > $"TheRebublicEdited.txt"