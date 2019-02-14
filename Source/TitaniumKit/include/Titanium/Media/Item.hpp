/**
 * TitaniumKit Titanium.Media.Item
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_MEDIA_ITEM_HPP_
#define _TITANIUM_MEDIA_ITEM_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/Media/Constants.hpp"
#include <chrono>

namespace Titanium
{
	class Blob;

	namespace Media
	{
		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Titanium Item Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Media.Item
		*/
		class TITANIUMKIT_EXPORT Item : public Module, public JSExport<Item>
		{

		public:

			/*!
			  @property
			  @abstract albumArtist
			  @discussion Artist credited for the album containing this item.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, albumArtist);

			/*!
			  @property
			  @abstract albumTitle
			  @discussion Title of the album containing this item.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, albumTitle);

			/*!
			  @property
			  @abstract albumTrackCount
			  @discussion Number of tracks for the album containing this item.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::uint32_t, albumTrackCount);

			/*!
			  @property
			  @abstract albumTrackNumber
			  @discussion Track number for this item.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::uint32_t, albumTrackNumber);

			/*!
			  @property
			  @abstract artist
			  @discussion Artist credited for this item.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, artist);

			/*!
			  @property
			  @abstract artwork
			  @discussion Image for the item's artwork as a `Blob` object,  or `null` if no artwork isavailable.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::shared_ptr<Titanium::Blob>, artwork);

			/*!
			  @property
			  @abstract composer
			  @discussion Composer of this item.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, composer);

			/*!
			  @property
			  @abstract discCount
			  @discussion Total number of discs for the album containing this item.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::uint32_t, discCount);

			/*!
			  @property
			  @abstract discNumber
			  @discussion Disc number for this item in the album.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::uint32_t, discNumber);

			/*!
			  @property
			  @abstract genre
			  @discussion Genre of this item.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, genre);

			/*!
			  @property
			  @abstract isCompilation
			  @discussion True if this item is part of a compilation album.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, isCompilation);

			/*!
			  @property
			  @abstract lyrics
			  @discussion Lyrics for this item.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, lyrics);

			/*!
			  @property
			  @abstract mediaType
			  @discussion The type of the media. 
			*/
			TITANIUM_PROPERTY_IMPL_DEF(MusicMediaType, mediaType);

			/*!
			  @property
			  @abstract playCount
			  @discussion Number of times the item has been played.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::uint32_t, playCount);

			/*!
			  @property
			  @abstract playbackDuration
			  @discussion Length (in seconds) of this item.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::chrono::seconds, playbackDuration);

			/*!
			  @property
			  @abstract podcastTitle
			  @discussion Title of a podcast item.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, podcastTitle);

			/*!
			  @property
			  @abstract rating
			  @discussion Rating for this item.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::uint32_t, rating);

			/*!
			  @property
			  @abstract skipCount
			  @discussion Number of times this item has been skipped.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::uint32_t, skipCount);

			/*!
			  @property
			  @abstract title
			  @discussion Title of this item.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, title);

			Item(const JSContext&) TITANIUM_NOEXCEPT;
			virtual ~Item()              = default;
			Item(const Item&)            = default;
			Item& operator=(const Item&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Item(Item&&)                 = default;
			Item& operator=(Item&&)      = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_READONLY_DEF(albumArtist);
			TITANIUM_PROPERTY_READONLY_DEF(albumTitle);
			TITANIUM_PROPERTY_READONLY_DEF(albumTrackCount);
			TITANIUM_PROPERTY_READONLY_DEF(albumTrackNumber);
			TITANIUM_PROPERTY_READONLY_DEF(artist);
			TITANIUM_PROPERTY_READONLY_DEF(artwork);
			TITANIUM_PROPERTY_READONLY_DEF(composer);
			TITANIUM_PROPERTY_READONLY_DEF(discCount);
			TITANIUM_PROPERTY_READONLY_DEF(discNumber);
			TITANIUM_PROPERTY_READONLY_DEF(genre);
			TITANIUM_PROPERTY_READONLY_DEF(isCompilation);
			TITANIUM_PROPERTY_READONLY_DEF(lyrics);
			TITANIUM_PROPERTY_READONLY_DEF(mediaType);
			TITANIUM_PROPERTY_READONLY_DEF(playCount);
			TITANIUM_PROPERTY_READONLY_DEF(playbackDuration);
			TITANIUM_PROPERTY_READONLY_DEF(podcastTitle);
			TITANIUM_PROPERTY_READONLY_DEF(rating);
			TITANIUM_PROPERTY_READONLY_DEF(skipCount);
			TITANIUM_PROPERTY_READONLY_DEF(title);

			TITANIUM_FUNCTION_DEF(getAlbumArtist);
			TITANIUM_FUNCTION_DEF(getAlbumTitle);
			TITANIUM_FUNCTION_DEF(getAlbumTrackCount);
			TITANIUM_FUNCTION_DEF(getAlbumTrackNumber);
			TITANIUM_FUNCTION_DEF(getArtist);
			TITANIUM_FUNCTION_DEF(getArtwork);
			TITANIUM_FUNCTION_DEF(getComposer);
			TITANIUM_FUNCTION_DEF(getDiscCount);
			TITANIUM_FUNCTION_DEF(getDiscNumber);
			TITANIUM_FUNCTION_DEF(getGenre);
			TITANIUM_FUNCTION_DEF(getIsCompilation);
			TITANIUM_FUNCTION_DEF(getLyrics);
			TITANIUM_FUNCTION_DEF(getMediaType);
			TITANIUM_FUNCTION_DEF(getPlayCount);
			TITANIUM_FUNCTION_DEF(getPlaybackDuration);
			TITANIUM_FUNCTION_DEF(getPodcastTitle);
			TITANIUM_FUNCTION_DEF(getRating);
			TITANIUM_FUNCTION_DEF(getSkipCount);
			TITANIUM_FUNCTION_DEF(getTitle);

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::string albumArtist__;
			std::string albumTitle__;
			std::uint32_t albumTrackCount__;
			std::uint32_t albumTrackNumber__;
			std::string artist__;
			std::shared_ptr<Titanium::Blob> artwork__;
			std::string composer__;
			std::uint32_t discCount__;
			std::uint32_t discNumber__;
			std::string genre__;
			bool isCompilation__;
			std::string lyrics__;
			MusicMediaType mediaType__;
			std::uint32_t playCount__;
			std::chrono::seconds playbackDuration__;
			std::string podcastTitle__;
			std::uint32_t rating__;
			std::uint32_t skipCount__;
			std::string title__;
#pragma warning(pop)
		};

	} // namespace Media
} // namespace Titanium
#endif // _TITANIUM_MEDIA_ITEM_HPP_