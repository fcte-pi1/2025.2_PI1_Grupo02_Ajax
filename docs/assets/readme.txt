In here we put images, pdfs and other graphical files. FOR THE LOVE OF GOD,
anything inside THIS FOLDER should NOT be mapped to mkdocs.yml. 

Also, IN THE NAME OF THE LORD, you WILL organize your graphical assets in categories
NEATLY. Failing to do so will GUARANTEE an UNORGANIZED AND INSUFERABLE HELL TO FIND ANYTHING!

Neatly means for every section inside the documentation, the used images should mirror the folder 
structure. Lets take an example from the block diagram:

inside docs we got this structure:

    /docs
        /arquitetura
            blocos.md
        index.md

And we reference the figure 1 blocos.png inside blocos.md. Then, inside assets, the mirror equivalent would be:
    /assets
        /arquitetura
            /blocos
                blocos.png

meaning if we used, say, 3 figures blocos1 blocos2 and blocos3, the structure would be:
    /assets
        /arquitetura
            /blocos
                blocos1.png
                blocos2.png
                blocos3.png

This way we can easily find what figures are in what document and also easily update 
and override such figures much easily. 

Conclusion: use common sense or else.

