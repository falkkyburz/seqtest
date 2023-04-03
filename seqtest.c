#include <stdio.h>
#include <time.h>
#include <assert.h>

typedef enum
{
    SEQ_STATE_1,
    SEQ_STATE_2,
    SEQ_STATE_3,
    SEQ_STATE_4,
    SEQ_STATE_5,
    SEQ_STATE_6,
    SEQ_STATE_7,
    SEQ_STATE_8,
    SEQ_STATE_ERROR,
    SEQ_STATE_END
} seq_name_e;

typedef seq_name_e (*seq_func_t)(void);

seq_name_e seq_state_1(void)
{
    printf("-- State 1 --\n");
    return SEQ_STATE_2;
}

seq_name_e seq_state_2(void)
{
    printf("-- State 2 --\n");
    return SEQ_STATE_3;
}

seq_name_e seq_state_3(void)
{
    printf("-- State 3 --\n");
    return SEQ_STATE_4;
}

seq_name_e seq_state_4(void)
{
    printf("-- State 4 --\n");
    return SEQ_STATE_5;
}

seq_name_e seq_state_5(void)
{
    printf("-- State 5 --\n");
    // simulate error
    if (clock() % 2)
    {
        return SEQ_STATE_6;
    }
    else
    {
        return SEQ_STATE_ERROR;
    }
}

seq_name_e seq_state_6(void)
{
    printf("-- State 6 --\n");
    return SEQ_STATE_7;
}

seq_name_e seq_state_7(void)
{
    printf("-- State 7 --\n");
    // simulate repeated steps
    if (clock() % 2)
    {
        return SEQ_STATE_8;
    }
    else
    {
        return SEQ_STATE_2;
    }
}

seq_name_e seq_state_8(void)
{
    printf("-- State 8 --\n");
    return SEQ_STATE_END;
}

seq_name_e seq_state_error(void)
{
    printf("-- State Error --\n");
    return SEQ_STATE_END;
}

seq_func_t seq_table[SEQ_STATE_END] = {
    [SEQ_STATE_1] = seq_state_1,        [SEQ_STATE_2] = seq_state_2,
    [SEQ_STATE_3] = seq_state_3,        [SEQ_STATE_4] = seq_state_4,
    [SEQ_STATE_5] = seq_state_5,        [SEQ_STATE_6] = seq_state_6,
    [SEQ_STATE_7] = seq_state_7,        [SEQ_STATE_8] = seq_state_8,
    [SEQ_STATE_ERROR] = seq_state_error};

int main(void)
{
    seq_name_e e_seq_state;

    printf("-- Start --\n");
    e_seq_state = SEQ_STATE_1;
    while (e_seq_state != SEQ_STATE_END)
    {
        assert(seq_table[e_seq_state] != NULL);
        e_seq_state = seq_table[e_seq_state]();
    }
    printf("-- End --\n");

    return 0;
}
