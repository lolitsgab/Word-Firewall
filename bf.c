//  bv.c
//  assingment1
//  Created by apple on 4/22/17.
//  Copyright © 2017 apple. All rights reserved.
//

# include <stdio.h>
# include <stdlib.h>
# include "bf.h"
# include "hash.h"

uint32_t hashBF ( bloomF * bf, char *key)
{
    return hash(bf -> s, key);
}
