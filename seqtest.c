#include <assert.h>
#include <stdio.h>
#include <time.h>

/******************************************************************************/
/*                                VARIANT 0                                   */
/******************************************************************************/

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
} seq0_name_e;

typedef seq0_name_e (*seq0_func_t)(void);

seq0_name_e seq_state_1(void)
{
    printf("-- State 1 --\n");
    return SEQ_STATE_2;
}

seq0_name_e seq_state_2(void)
{
    printf("-- State 2 --\n");
    return SEQ_STATE_3;
}

seq0_name_e seq_state_3(void)
{
    printf("-- State 3 --\n");
    return SEQ_STATE_4;
}

seq0_name_e seq_state_4(void)
{
    printf("-- State 4 --\n");
    return SEQ_STATE_5;
}

seq0_name_e seq_state_5(void)
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

seq0_name_e seq_state_6(void)
{
    printf("-- State 6 --\n");
    return SEQ_STATE_7;
}

seq0_name_e seq_state_7(void)
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

seq0_name_e seq_state_8(void)
{
    printf("-- State 8 --\n");
    return SEQ_STATE_END;
}

seq0_name_e seq_state_error(void)
{
    printf("-- State Error --\n");
    return SEQ_STATE_END;
}

seq0_func_t seq0_table[SEQ_STATE_END] = {
    [SEQ_STATE_1] = seq_state_1,        [SEQ_STATE_2] = seq_state_2,
    [SEQ_STATE_3] = seq_state_3,        [SEQ_STATE_4] = seq_state_4,
    [SEQ_STATE_5] = seq_state_5,        [SEQ_STATE_6] = seq_state_6,
    [SEQ_STATE_7] = seq_state_7,        [SEQ_STATE_8] = seq_state_8,
    [SEQ_STATE_ERROR] = seq_state_error};

void run_variant0(void)
{
    seq0_name_e e_seq_state;

    printf("-- Start Variant 0 --\n");
    e_seq_state = SEQ_STATE_1;
    while (e_seq_state != SEQ_STATE_END)
    {
        assert(seq0_table[e_seq_state] != NULL);
        e_seq_state = seq0_table[e_seq_state]();
    }
    printf("-- End Variant 0 --\n");
}

/******************************************************************************/
/*                                VARIANT 1                                   */
/******************************************************************************/

typedef enum seq1_ret_e
{
    SEQ_NEXT,
    SEQ_GOTO,
    SEQ_ERROR,
    SEQ_SIZE /* do not use as return value */
} seq1_ret_e;

seq1_ret_e seq_func_1(void)
{
    printf("-- Func 1 --\n");
    return SEQ_NEXT;
}

seq1_ret_e seq_func_2(void)
{
    static int cnt = 0;
    printf("-- Func 2 --\n");

    if (cnt < 1)
    {
        cnt += 1;
        return SEQ_GOTO;
    }
    else
    {
        return SEQ_NEXT;
    }
}

seq1_ret_e seq_func_3(void)
{
    printf("-- Func 3 --\n");
    return SEQ_NEXT;
}

seq1_ret_e seq_func_4(void)
{
    printf("-- Func 4 --\n");
    return SEQ_NEXT;
}

seq1_ret_e seq_func_5(void)
{
    printf("-- Func 5 --\n");
    // simulate error
    if (clock() % 2)
    {
        return SEQ_NEXT;
    }
    else
    {
        return SEQ_ERROR;
    }
}

seq1_ret_e seq_func_6(void)
{
    printf("-- Func 6 --\n");
    return SEQ_NEXT;
}

seq1_ret_e seq_func_7(void)
{
    printf("-- Func 7 --\n");
    // simulate repeated steps
    if (clock() % 2)
    {
        return SEQ_NEXT;
    }
    else
    {
        return SEQ_GOTO;
    }
}

seq1_ret_e seq_func_8(void)
{
    printf("-- Func 8 --\n");
    return SEQ_GOTO;
}

seq1_ret_e seq_func_error(void)
{
    printf("-- Func Error --\n");
    return SEQ_GOTO;
}

typedef enum seq1_func_e
{
    SEQ_FUNC_1,
    SEQ_FUNC_2,
    SEQ_FUNC_3,
    SEQ_FUNC_4,
    SEQ_FUNC_5,
    SEQ_FUNC_6,
    SEQ_FUNC_7,
    SEQ_FUNC_8,
    SEQ_FUNC_ERROR,
    SEQ_FUNC_END
} seq1_func_e;

typedef struct
{
    seq1_ret_e (*pf_run)(void);
    seq1_func_e e_link[SEQ_SIZE];
} seq1_link_t;

seq1_link_t seq1_table[SEQ_FUNC_END] = {
    /* pf_run  ,  NEXT      , GOTO        , ERROR         */
    {seq_func_1, {SEQ_FUNC_2, SEQ_FUNC_END, SEQ_FUNC_ERROR}},
    {seq_func_2, {SEQ_FUNC_3, SEQ_FUNC_2, SEQ_FUNC_ERROR}},
    {seq_func_3, {SEQ_FUNC_4, SEQ_FUNC_END, SEQ_FUNC_ERROR}},
    {seq_func_4, {SEQ_FUNC_5, SEQ_FUNC_END, SEQ_FUNC_ERROR}},
    {seq_func_5, {SEQ_FUNC_6, SEQ_FUNC_END, SEQ_FUNC_ERROR}},
    {seq_func_6, {SEQ_FUNC_7, SEQ_FUNC_END, SEQ_FUNC_ERROR}},
    {seq_func_7, {SEQ_FUNC_8, SEQ_FUNC_2, SEQ_FUNC_ERROR}},
    {seq_func_8, {SEQ_FUNC_END, SEQ_FUNC_END, SEQ_FUNC_ERROR}},
    {seq_func_error, {SEQ_FUNC_END, SEQ_FUNC_END, SEQ_FUNC_END}}};

void run_variant1(void)
{
    seq1_func_e e_seq_func;
    seq1_ret_e e_ret;

    printf("-- Start Variant 1 --\n");
    e_seq_func = SEQ_FUNC_1;
    while (e_seq_func != SEQ_FUNC_END)
    {
        assert(seq1_table[e_seq_func].pf_run != NULL);
        e_ret = seq1_table[e_seq_func].pf_run();
        e_seq_func = seq1_table[e_seq_func].e_link[e_ret];
    }
    printf("-- End Variant 1 --\n");
}

/******************************************************************************/
/*                                   MAIN                                     */
/******************************************************************************/

int main(void)
{
    run_variant0();
    run_variant1();

    return 0;
}
