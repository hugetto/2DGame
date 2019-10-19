//==============================================================================
/*
    Renderable Class
    Hug Beneit
*/
//==============================================================================

#ifndef __CSOUNDPROXY_H__
#define __CSOUNDPROXY_H__

#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>

namespace hugGameEngine
{
    class CGameObject;

    class CSoundProxy
    {
    protected:
        static CSoundProxy sSoundProxyInstance;
    public:
        enum class EPosition { E_FIXED, E_ABSOLUTE };
    private:

        std::vector< Mix_Music* >       mMusicList;
        std::vector< std::string >      mMusicName;
        std::vector< unsigned int >     mMusicCount;

        std::vector< Mix_Chunk* >       mChunkList;
        std::vector< std::string >      mChunkName;
        std::vector< unsigned int >     mChunkCount;
    public:
                            CSoundProxy       () {}
                           ~CSoundProxy       ();
                            CSoundProxy       (const CSoundProxy& aGo) = delete;
                            CSoundProxy& operator= (const CSoundProxy&) = delete;
        Mix_Music*          CreateMusic         (const char* aMusicFile);
        Mix_Chunk*          CreateChunk         (const char* aMusicFile);
        bool                DestroyMusic        (Mix_Music* aMusic);
        bool                DestroyChunk        (Mix_Chunk* aChunk);
        static CSoundProxy* GetInstance         ()          { return &CSoundProxy::sSoundProxyInstance; }
    };
}
#endif

