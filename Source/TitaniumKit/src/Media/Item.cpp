/**
 * TitaniumKit Titanium.Media.Item
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Media/Item.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Media
	{

		Item::Item(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.Media.Item")
			, albumArtist__("")
			, albumTitle__("")
			, albumTrackCount__(0)
			, albumTrackNumber__(0)
			, artist__("")
			, composer__("")
			, discCount__(0)
			, discNumber__(0)
			, genre__("")
			, isCompilation__(false)
			, lyrics__("")
			, mediaType__(MusicMediaType::All)
			, playCount__(0)
			, playbackDuration__(0)
			, podcastTitle__("")
			, rating__(0)
			, skipCount__(0)
			, title__("")
		{
		}

		TITANIUM_PROPERTY_READWRITE(Item, std::string, albumArtist)
		TITANIUM_PROPERTY_READWRITE(Item, std::string, albumTitle)
		TITANIUM_PROPERTY_READWRITE(Item, std::uint32_t, albumTrackCount)
		TITANIUM_PROPERTY_READWRITE(Item, std::uint32_t, albumTrackNumber)
		TITANIUM_PROPERTY_READWRITE(Item, std::string, artist)
		TITANIUM_PROPERTY_READWRITE(Item, std::shared_ptr<Titanium::Blob>, artwork)
		TITANIUM_PROPERTY_READWRITE(Item, std::string, composer)
		TITANIUM_PROPERTY_READWRITE(Item, std::uint32_t, discCount)
		TITANIUM_PROPERTY_READWRITE(Item, std::uint32_t, discNumber)
		TITANIUM_PROPERTY_READWRITE(Item, std::string, genre)
		TITANIUM_PROPERTY_READWRITE(Item, bool, isCompilation)
		TITANIUM_PROPERTY_READWRITE(Item, std::string, lyrics)
		TITANIUM_PROPERTY_READWRITE(Item, MusicMediaType, mediaType)
		TITANIUM_PROPERTY_READWRITE(Item, std::uint32_t, playCount)
		TITANIUM_PROPERTY_READWRITE(Item, std::chrono::seconds, playbackDuration)
		TITANIUM_PROPERTY_READWRITE(Item, std::string, podcastTitle)
		TITANIUM_PROPERTY_READWRITE(Item, std::uint32_t, rating)
		TITANIUM_PROPERTY_READWRITE(Item, std::uint32_t, skipCount)
		TITANIUM_PROPERTY_READWRITE(Item, std::string, title)

		void Item::JSExportInitialize()
		{
			JSExport<Item>::SetClassVersion(1);
			JSExport<Item>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(Item, albumArtist);
			TITANIUM_ADD_PROPERTY_READONLY(Item, albumTitle);
			TITANIUM_ADD_PROPERTY_READONLY(Item, albumTrackCount);
			TITANIUM_ADD_PROPERTY_READONLY(Item, albumTrackNumber);
			TITANIUM_ADD_PROPERTY_READONLY(Item, artist);
			TITANIUM_ADD_PROPERTY_READONLY(Item, artwork);
			TITANIUM_ADD_PROPERTY_READONLY(Item, composer);
			TITANIUM_ADD_PROPERTY_READONLY(Item, discCount);
			TITANIUM_ADD_PROPERTY_READONLY(Item, discNumber);
			TITANIUM_ADD_PROPERTY_READONLY(Item, genre);
			TITANIUM_ADD_PROPERTY_READONLY(Item, isCompilation);
			TITANIUM_ADD_PROPERTY_READONLY(Item, lyrics);
			TITANIUM_ADD_PROPERTY_READONLY(Item, mediaType);
			TITANIUM_ADD_PROPERTY_READONLY(Item, playCount);
			TITANIUM_ADD_PROPERTY_READONLY(Item, playbackDuration);
			TITANIUM_ADD_PROPERTY_READONLY(Item, podcastTitle);
			TITANIUM_ADD_PROPERTY_READONLY(Item, rating);
			TITANIUM_ADD_PROPERTY_READONLY(Item, skipCount);
			TITANIUM_ADD_PROPERTY_READONLY(Item, title);

			TITANIUM_ADD_FUNCTION(Item, getAlbumArtist);
			TITANIUM_ADD_FUNCTION(Item, getAlbumTitle);
			TITANIUM_ADD_FUNCTION(Item, getAlbumTrackCount);
			TITANIUM_ADD_FUNCTION(Item, getAlbumTrackNumber);
			TITANIUM_ADD_FUNCTION(Item, getArtist);
			TITANIUM_ADD_FUNCTION(Item, getArtwork);
			TITANIUM_ADD_FUNCTION(Item, getComposer);
			TITANIUM_ADD_FUNCTION(Item, getDiscCount);
			TITANIUM_ADD_FUNCTION(Item, getDiscNumber);
			TITANIUM_ADD_FUNCTION(Item, getGenre);
			TITANIUM_ADD_FUNCTION(Item, getIsCompilation);
			TITANIUM_ADD_FUNCTION(Item, getLyrics);
			TITANIUM_ADD_FUNCTION(Item, getMediaType);
			TITANIUM_ADD_FUNCTION(Item, getPlayCount);
			TITANIUM_ADD_FUNCTION(Item, getPlaybackDuration);
			TITANIUM_ADD_FUNCTION(Item, getPodcastTitle);
			TITANIUM_ADD_FUNCTION(Item, getRating);
			TITANIUM_ADD_FUNCTION(Item, getSkipCount);
			TITANIUM_ADD_FUNCTION(Item, getTitle);
		}

		TITANIUM_PROPERTY_GETTER_STRING(Item, albumArtist)
		TITANIUM_PROPERTY_GETTER_STRING(Item, albumTitle)
		TITANIUM_PROPERTY_GETTER_STRING(Item, artist)
		TITANIUM_PROPERTY_GETTER_OBJECT(Item, artwork)
		TITANIUM_PROPERTY_GETTER_STRING(Item, composer)
		TITANIUM_PROPERTY_GETTER_STRING(Item, genre)
		TITANIUM_PROPERTY_GETTER_BOOL(Item, isCompilation)
		TITANIUM_PROPERTY_GETTER_STRING(Item, lyrics)
		TITANIUM_PROPERTY_GETTER_STRING(Item, podcastTitle)
		TITANIUM_PROPERTY_GETTER_STRING(Item, title)
		TITANIUM_PROPERTY_GETTER_UINT(Item, rating)
		TITANIUM_PROPERTY_GETTER_UINT(Item, discCount)
		TITANIUM_PROPERTY_GETTER_UINT(Item, playCount)
		TITANIUM_PROPERTY_GETTER_UINT(Item, skipCount)
		TITANIUM_PROPERTY_GETTER_UINT(Item, discNumber)
		TITANIUM_PROPERTY_GETTER_UINT(Item, albumTrackCount)
		TITANIUM_PROPERTY_GETTER_UINT(Item, albumTrackNumber)
		TITANIUM_PROPERTY_GETTER_TIME(Item, playbackDuration)
		TITANIUM_PROPERTY_GETTER_ENUM(Item, mediaType)

		TITANIUM_FUNCTION_AS_GETTER(Item, getAlbumArtist, albumArtist)
		TITANIUM_FUNCTION_AS_GETTER(Item, getAlbumTitle, albumTitle)
		TITANIUM_FUNCTION_AS_GETTER(Item, getAlbumTrackCount, albumTrackCount)
		TITANIUM_FUNCTION_AS_GETTER(Item, getAlbumTrackNumber, albumTrackNumber)
		TITANIUM_FUNCTION_AS_GETTER(Item, getArtist, artist)
		TITANIUM_FUNCTION_AS_GETTER(Item, getArtwork, artwork)
		TITANIUM_FUNCTION_AS_GETTER(Item, getComposer, composer)
		TITANIUM_FUNCTION_AS_GETTER(Item, getDiscCount, discCount)
		TITANIUM_FUNCTION_AS_GETTER(Item, getDiscNumber, discNumber)
		TITANIUM_FUNCTION_AS_GETTER(Item, getGenre, genre)
		TITANIUM_FUNCTION_AS_GETTER(Item, getIsCompilation, isCompilation)
		TITANIUM_FUNCTION_AS_GETTER(Item, getLyrics, lyrics)
		TITANIUM_FUNCTION_AS_GETTER(Item, getMediaType, mediaType)
		TITANIUM_FUNCTION_AS_GETTER(Item, getPlayCount, playCount)
		TITANIUM_FUNCTION_AS_GETTER(Item, getPlaybackDuration, playbackDuration)
		TITANIUM_FUNCTION_AS_GETTER(Item, getPodcastTitle, podcastTitle)
		TITANIUM_FUNCTION_AS_GETTER(Item, getRating, rating)
		TITANIUM_FUNCTION_AS_GETTER(Item, getSkipCount, skipCount)
		TITANIUM_FUNCTION_AS_GETTER(Item, getTitle, title)

	} // namespace Media
} // namespace Titanium
