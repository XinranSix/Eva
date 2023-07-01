/**
 * @file    :   MouseCodes.h
 * @date    :   2023/06/27 23:32:07
 * @author  :   Yao J
 * @version :   1.0
 */

#pragma once

namespace Eva {
    using MouseCode = short int;

    namespace Mouse {
        enum : MouseCode {
            // From glfw3.h
            Button0 = 0,
            Button1 = 1,
            Button2 = 2,
            Button3 = 3,
            Button4 = 4,
            Button5 = 5,
            Button6 = 6,
            Button7 = 7,

            ButtonLast = Button7,
            ButtonLeft = Button0,
            ButtonRight = Button1,
            ButtonMiddle = Button2
        };
    }
} // namespace Eva
