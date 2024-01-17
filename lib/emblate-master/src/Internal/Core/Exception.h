#ifndef EMBLATE_EXCEPTION_H
#define EMBLATE_EXCEPTION_H

namespace Emblate
{
    /**
     * Defines a type of object to be thrown as exception. It reports
     * errors for missing code implementations.
     */
    class not_implemented {};

    /**
     * Defines a type of object to be thrown as exception. It reports
     * errors that arise because an argument value has not been accepted.
     */
    class invalid_argument {};

    /**
     * Defines a type of object to be thrown as exception. It reports
     * errors that are consequence of attempt to access elements out of
     * defined range.
     */
    class out_of_range {};
}

#endif /* EMBLATE_EXCEPTION_H */
