# HaaraGame Todo List

#### [X] Screen States
    Simple Enum to enumerate the screens, necessary to add mode values on screen creation.
    Simple Struct to control which screen has methods or not.
    Struct methods avaliable currently:
        - Initialize;
        - Destroy;
        - Update;

    Quite usable ;D
---

#### [X] Simple Sprite System
    Created a sprite struct with some usable struct & types.
    Created a method to render it.
---

#### [ ] Simple Animation System
    Ongoing...
---

#### [ ] Rendering Stack
    Look at samples on internet.

    Early thoughts: "I think i will just find a way to create a struct 'stack' which has an dynamic type stack, the dynamic type stack will receive other struct types that have a certain pattern".
    
    Which one?
        - The "dynamic" structs should have some certain "render"
    Or ...
        - Will have a switch-case to look at the struct type then use the correct render type for the struct.

    Renderable struct types examples...
    - HGText
    - HGRectangle
    - HGLine
---

#### [ ] Layer System
    Look at samples on internet

    "Thinking of a Stack of layerable structs, don't know where to start :c
---
