Martock: Standards
================================================================================

Environment
--------------------------------------------------------------------------------
The repository should only depend on text files and build scripts (either
configure/make files or shell scripts, whichever is appropriate at the time).
Don't commit IDE files.

Platforms
--------------------------------------------------------------------------------
Martock targets two platforms: Windows and *buntu Linux distributions. Martock
should not depend on any tools or code that isolate it to a specific platform.

Coding Standards
--------------------------------------------------------------------------------
Martock follows a modified version of the Linux Kernel coding standards.

Indentation should be 8 spaces, not tabs; no tabs.

Only one statement per line.

    /* GOOD */
    if (something)
            do_this();
    x = 7;
    b = 7;
    c = 7;

    /* BAD */
    if (something) do_this();
    x = b = c = 7;

Braces should directly follow the relevant statement.

    /* GOOD */
    if (something) {
            x = 2;
    } else if {
            x = 3;
    }

    /* BAD */
    if (something)
    {
            x = 2;
    }
    else if
    {
            x = 3;
    }

The one exception to this is functions, which are special.

    void mute ()
    {

Function headers should include a space before the parenthesis for parameters,
like illustrated just above.

Semicolons should directly follow the end of a line, with no preceding space.

    /* GOOD */
    int x = 9;

    /* BAD */
    int x = 9 ;

Every function accessible outside of file scope should have a comment block
above it in this format.

    /**
     *  Explain what the function should do (the goal), not how it does so.
     *
     *  @num1: what does this variable have to with the goal outline above?
     *  @num2: what about this one?
     *
     *  @return: what does the return mean to someone using this function?
     */
    int add_nums (int num1, int num2)
    {
        return num1 + num2;
    }

Variable names should be relevant only to their scope. If global, describe how
it is relevant to the whole program; if in a small scope, name it only according
to what it does in it's function.

For compound words in identifiers, use underscores instead of camel case for
readability.

    /* GOOD */
    void client_name ();

    /* BAD */
    void clientName ();

Pointers and casts should include parenthesis for clarity, and the asterisk
should hover near the variable, not the type. Pointers declared before a value
is set should be set to NULL.

    /* GOOD */
    char *ptr = NULL;
    int x = (int*)ptr;

    /* BAD */
    char* ptr;
    int x = (int*) ptr;

Lines should not exceed 80 characters. No Exceptions. When this limit becomes an
issue, your function is probably too complicated. Some content is long still,
and must be broken into parts. When this happens, adhere to common sense. Refer
to the example below.

    int retval = crypto_box(plaintext,
                            ciphertext,
                            nonce,
                            prefix,
                            public_key,
                            secret_key);
    printf("........................."
           ".........................");
