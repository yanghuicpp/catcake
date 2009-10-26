/*
    Copyright (c) 2007-2009 Takashi Kitao
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    1. Redistributions of source code must retain the above copyright
    `  notice, this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright
    `  notice, this list of conditions and the following disclaimer in the
    `  documentation and/or other materials provided with the distribution.

    3. The name of the author may not be used to endorse or promote products
    `  derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
    IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
    OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
    IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
    NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
    THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "test.h"


void ckRend_ShaderTest()
{
    /*
        void init(ckPrim* prim, ckID shd_id)
        void init(ckPrim* prim, r32* rend_data, ckID shd_id)
        ckID getShaderID()
        ckID get2ndTextureID()
        void set2ndTextureID(ckID tex_id)
        ckID get3rdTextureID()
        void set3rdTextureID(ckID tex_id)
        r32& uniform(u8 uni_index)
        void setUniformVec(u8 uni_index, const ckVec& vec)
        void setUniformCol3x255(u8 uni_index, ckCol col)
        void setUniformCol4x255(u8 uni_index, ckCol col)
        r32& attrib(u16 data_index, u8 att_index)
        void setAttribVec(u16 data_index, u8 att_index, const ckVec& vec)
        void setAttribCol3x255(u16 data_index, u8 att_index, ckCol col)
        void setAttribCol4x255(u16 data_index, u8 att_index, ckCol col)
    */
    {
        static const char s_vert_code[] = "void main() { gl_Position = 0.0; }";
        static const char s_frag_code[] = "void main() { gl_FragColor = 1.0; }";

        ckDrawMgr::createAfterRes();
        ckDrawMgr::newTexture(ckID_("TEST"), 16, 16, ckTex::FORMAT_RGB);

        ckShd* shd1 = ckDrawMgr::newShader(ckID::genID(), s_vert_code, s_frag_code, 0, 0, 0);
        ckShd* shd2 = ckDrawMgr::newShader(ckID::genID(), s_vert_code, s_frag_code, 4, 5, 0);

        ckRend_Shader rend_shd;

        ckAssertThrow(rend_shd.getShaderID(), ckRend::ExceptionNotInitialized);
        ckAssertThrow(rend_shd.get2ndTextureID(), ckRend::ExceptionNotInitialized);
        ckAssertThrow(rend_shd.set2ndTextureID(ckID::ZERO), ckRend::ExceptionNotInitialized);
        ckAssertThrow(rend_shd.get3rdTextureID(), ckRend::ExceptionNotInitialized);
        ckAssertThrow(rend_shd.set3rdTextureID(ckID::ZERO), ckRend::ExceptionNotInitialized);
        ckAssertThrow(rend_shd.uniform(0), ckRend::ExceptionNotInitialized);
        ckAssertThrow(rend_shd.setUniformVec(0, ckVec::ZERO), ckRend::ExceptionNotInitialized);
        ckAssertThrow(rend_shd.setUniformCol3x255(0, ckCol::ZERO), ckRend::ExceptionNotInitialized);
        ckAssertThrow(rend_shd.setUniformCol4x255(0, ckCol::ZERO), ckRend::ExceptionNotInitialized);
        ckAssertThrow(rend_shd.attrib(0, 0), ckRend::ExceptionNotInitialized);
        ckAssertThrow(rend_shd.setAttribVec(0, 0, ckVec::ZERO), ckRend::ExceptionNotInitialized);
        ckAssertThrow(rend_shd.setAttribCol3x255(0, 0, ckCol::ZERO), ckRend::ExceptionNotInitialized);
        ckAssertThrow(rend_shd.setAttribCol4x255(0, 0, ckCol::ZERO), ckRend::ExceptionNotInitialized);

        ckPrim prim;

        prim.init(ckPrim::MODE_LINES, 2, ckDrawMgr::DEFAULT_2D_SCREEN_ID);
        rend_shd.init(&prim, shd1->getID());

        ckAssert(rend_shd.getShaderID() == shd1->getID());
        ckAssert(rend_shd.get2ndTextureID() == ckID::ZERO);
        ckAssert(rend_shd.get3rdTextureID() == ckID::ZERO);

        ckAssertThrow(rend_shd.uniform(0), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.setUniformVec(0, ckVec::ZERO), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.setUniformCol3x255(0, ckCol::ZERO), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.setUniformCol4x255(0, ckCol::ZERO), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.attrib(2, 0), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.attrib(0, 0), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.setAttribVec(2, 0, ckVec::ZERO), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.setAttribVec(0, 0, ckVec::ZERO), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.setAttribCol3x255(2, 0, ckCol::ZERO), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.setAttribCol3x255(2, 0, ckCol::ZERO), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.setAttribCol4x255(0, 0, ckCol::ZERO), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.setAttribCol4x255(0, 0, ckCol::ZERO), ckRend::ExceptionInvalidArgument);

        ckDrawMgr::renderForSystem();

        prim.init(ckPrim::MODE_LINES, 3, ckDrawMgr::DEFAULT_2D_SCREEN_ID);
        rend_shd.init(&prim, shd2->getID());

        ckAssert(rend_shd.getShaderID() == shd2->getID());
        ckAssert(rend_shd.get2ndTextureID() == ckID::ZERO);
        ckAssert(rend_shd.get3rdTextureID() == ckID::ZERO);

        rend_shd.set2ndTextureID(ckID::ZERO);
        ckAssert(rend_shd.get2ndTextureID() == ckID::ZERO);

        rend_shd.set3rdTextureID(ckID::ZERO);
        ckAssert(rend_shd.get3rdTextureID() == ckID::ZERO);

        for (s32 i = 0; i < 4; i++)
        {
            rend_shd.uniform(0) = static_cast<r32>(i);
            ckAssert(isEqual(rend_shd.uniform(0), static_cast<r32>(i)));
        }

        rend_shd.setUniformVec(1, ckVec(10.0f, 20.0f, 30.0f));
        ckAssert(isEqual(rend_shd.uniform(1), 10.0f) && isEqual(rend_shd.uniform(2), 20.0f) && isEqual(rend_shd.uniform(3), 30.0f));

        rend_shd.setUniformCol3x255(1, ckCol(11, 22, 33));
        ckAssert(isEqual(rend_shd.uniform(1), 11.0f) && isEqual(rend_shd.uniform(2), 22.0f) && isEqual(rend_shd.uniform(3), 33.0f));

        rend_shd.setUniformCol4x255(0, ckCol(1, 2, 3, 4));
        ckAssert(isEqual(rend_shd.uniform(0), 1.0f) && isEqual(rend_shd.uniform(1), 2.0f) && //
            isEqual(rend_shd.uniform(2), 3.0f) && isEqual(rend_shd.uniform(3), 4.0f));

        for (s32 i = 0; i < 3; i++)
        {
            for (s32 j = 0; j < 5; j++)
            {
                rend_shd.attrib(i, j) = static_cast<r32>(i + j);
                ckAssert(isEqual(rend_shd.attrib(i, j), static_cast<r32>(i + j)));
            }

            rend_shd.setAttribVec(i, 2, ckVec(10.0f + i, 11.0f + i, 12.0f + i));
            ckAssert(isEqual(rend_shd.attrib(i, 2), 10.0f + i) && isEqual(rend_shd.attrib(i, 3), 11.0f + i) && isEqual(rend_shd.attrib(i, 4), 12.0f + i));

            rend_shd.setAttribCol3x255(i, 2, ckCol(i + 2, i + 3, i + 4));
            ckAssert(isEqual(rend_shd.attrib(i, 2), 2.0f + i) && isEqual(rend_shd.attrib(i, 3), 3.0f + i) && isEqual(rend_shd.attrib(i, 4), 4.0f + i));

            rend_shd.setAttribCol4x255(i, 1, ckCol(i + 5, i + 6, i + 7, i + 8));
            ckAssert(isEqual(rend_shd.attrib(i, 1), 5.0f + i) && isEqual(rend_shd.attrib(i, 2), 6.0f + i) && //
                isEqual(rend_shd.attrib(i, 3), 7.0f + i) && isEqual(rend_shd.attrib(i, 4), 8.0f + i));
        }

        ckAssertThrow(rend_shd.uniform(4), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.setUniformVec(2, ckVec::ZERO), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.setUniformCol3x255(2, ckCol::ZERO), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.setUniformCol4x255(1, ckCol::ZERO), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.attrib(3, 0), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.attrib(0, 5), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.setAttribVec(3, 0, ckVec::ZERO), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.setAttribVec(0, 3, ckVec::ZERO), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.setAttribCol3x255(3, 0, ckCol::ZERO), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.setAttribCol3x255(0, 3, ckCol::ZERO), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.setAttribCol4x255(3, 0, ckCol::ZERO), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.setAttribCol4x255(0, 2, ckCol::ZERO), ckRend::ExceptionInvalidArgument);

        ckDrawMgr::renderForSystem();

        ckAssertThrow(rend_shd.set2ndTextureID(ckID::genID()), ckDrawMgr::ExceptionNotFound);
        ckAssertThrow(rend_shd.set3rdTextureID(ckID::genID()), ckDrawMgr::ExceptionNotFound);
        ckAssertThrow(rend_shd.init(NULL, shd1->getID()), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.init(&prim, ckID::ZERO), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.init(&prim, ckID::genID()), ckDrawMgr::ExceptionNotFound);
        ckAssertThrow(rend_shd.init(&prim, NULL, shd2->getID()), ckRend::ExceptionInvalidCall);

        ckPrim::PrimData prim_data[3];
        r32 rend_data[3];

        prim.init(ckPrim::MODE_LINES, prim_data, 3, ckDrawMgr::DEFAULT_2D_SCREEN_ID);
        rend_shd.init(&prim, rend_data, shd2->getID());

        ckAssertThrow(rend_shd.init(NULL, rend_data, shd2->getID()), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.init(&prim, NULL, shd2->getID()), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.init(&prim, rend_data, ckID::ZERO), ckRend::ExceptionInvalidArgument);
        ckAssertThrow(rend_shd.init(&prim, rend_data, ckID::genID()), ckDrawMgr::ExceptionNotFound);
        ckAssertThrow(rend_shd.init(&prim, shd2->getID()), ckRend::ExceptionInvalidCall);

        ckDrawMgr::destroyBeforeRes();
    }
}