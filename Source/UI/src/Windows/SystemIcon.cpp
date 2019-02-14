/**
* Windows module
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#include "TitaniumWindows/UI/Windows/SystemIcon.hpp"
#include "TitaniumWindows/UI/Windows/CommandBar.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		namespace WindowsXaml
		{
			using namespace Windows::UI::Xaml;

			SystemIcon::SystemIcon(const JSContext& js_context) TITANIUM_NOEXCEPT
				: Titanium::Module(js_context, "Ti.UI.Windows.SystemIcon")
				, previous__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Previous)))
				, next__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Next)))
				, play__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Play)))
				, pause__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Pause)))
				, edit__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Edit)))
				, save__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Save)))
				, clear__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Clear)))
				, delete__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Delete)))
				, remove__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Remove)))
				, add__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Add)))
				, cancel__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Cancel)))
				, accept__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Accept)))
				, more__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::More)))
				, redo__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Redo)))
				, undo__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Undo)))
				, home__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Home)))
				, up__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Up)))
				, forward__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Forward)))
				, back__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Back)))
				, favorite__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Favorite)))
				, camera__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Camera)))
				, setting__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Setting)))
				, video__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Video)))
				, sync__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Sync)))
				, download__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Download)))
				, mail__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Mail)))
				, find__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Find)))
				, help__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Help)))
				, upload__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Upload)))
				, emoji__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Emoji)))
				, twopage__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::TwoPage)))
				, leavechat__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::LeaveChat)))
				, mailforward__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::MailForward)))
				, clock__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Clock)))
				, send__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Send)))
				, crop__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Crop)))
				, rotatecamera__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::RotateCamera)))
				, people__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::People)))
				, openpane__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::OpenPane)))
				, closepane__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::ClosePane)))
				, world__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::World)))
				, flag__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Flag)))
				, previewlink__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::PreviewLink)))
				, globe__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Globe)))
				, trim__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Trim)))
				, attachcamera__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::AttachCamera)))
				, zoomin__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::ZoomIn)))
				, bookmarks__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Bookmarks)))
				, document__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Document)))
				, protecteddocument__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::ProtectedDocument)))
				, page__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Page)))
				, bullets__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Bullets)))
				, comment__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Comment)))
				, mailfilled__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::MailFilled)))
				, contactinfo__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::ContactInfo)))
				, hangup__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::HangUp)))
				, viewall__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::ViewAll)))
				, mappin__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::MapPin)))
				, phone__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Phone)))
				, videochat__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::VideoChat)))
				, switch__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Switch)))
				, contact__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Contact)))
				, rename__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Rename)))
				, pin__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Pin)))
				, musicinfo__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::MusicInfo)))
				, go__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Go)))
				, keyboard__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Keyboard)))
				, dockleft__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::DockLeft)))
				, dockright__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::DockRight)))
				, dockbottom__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::DockBottom)))
				, remote__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Remote)))
				, refresh__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Refresh)))
				, rotate__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Rotate)))
				, shuffle__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Shuffle)))
				, list__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::List)))
				, shop__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Shop)))
				, selectall__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::SelectAll)))
				, orientation__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Orientation)))
				, import__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Import)))
				, importall__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::ImportAll)))
				, browsephotos__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::BrowsePhotos)))
				, webcam__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::WebCam)))
				, pictures__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Pictures)))
				, savelocal__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::SaveLocal)))
				, caption__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Caption)))
				, stop__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Stop)))
				, showresults__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::ShowResults)))
				, volume__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Volume)))
				, repair__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Repair)))
				, message__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Message)))
				, page2__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Page2)))
				, calendarday__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::CalendarDay)))
				, calendarweek__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::CalendarWeek)))
				, calendar__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Calendar)))
				, character__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Character)))
				, mailreplyall__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::MailReplyAll)))
				, read__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Read)))
				, link__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Link)))
				, account__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Account)))
				, showbcc__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::ShowBcc)))
				, hidebcc__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::HideBcc)))
				, cut__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Cut)))
				, attach__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Attach)))
				, paste__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Paste)))
				, filter__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Filter)))
				, copy__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Copy)))
				, emoji2__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Emoji2)))
				, important__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Important)))
				, mailreply__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::MailReply)))
				, slideshow__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::SlideShow)))
				, sort__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Sort)))
				, manage__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Manage)))
				, allapps__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::AllApps)))
				, disconnectdrive__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::DisconnectDrive)))
				, mapdrive__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::MapDrive)))
				, newwindow__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::NewWindow)))
				, openwith__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::OpenWith)))
				, contactpresence__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::ContactPresence)))
				, priority__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Priority)))
				, gototoday__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::GoToToday)))
				, font__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Font)))
				, fontcolor__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::FontColor)))
				, contact2__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Contact2)))
				, folder__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Folder)))
				, audio__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Audio)))
				, placeholder__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Placeholder)))
				, view__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::View)))
				, setlockscreen__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::SetLockScreen)))
				, settile__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::SetTile)))
				, closedcaption__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::ClosedCaption)))
				, stopslideshow__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::StopSlideShow)))
				, permissions__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Permissions)))
				, highlight__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Highlight)))
				, disableupdates__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::DisableUpdates)))
				, unfavorite__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::UnFavorite)))
				, unpin__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::UnPin)))
				, openlocal__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::OpenLocal)))
				, mute__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Mute)))
				, italic__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Italic)))
				, underline__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Underline)))
				, bold__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Bold)))
				, movetofolder__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::MoveToFolder)))
				, likedislike__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::LikeDislike)))
				, dislike__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Dislike)))
				, like__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Like)))
				, alignright__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::AlignRight)))
				, aligncenter__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::AlignCenter)))
				, alignleft__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::AlignLeft)))
				, zoom__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Zoom)))
				, zoomout__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::ZoomOut)))
				, openfile__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::OpenFile)))
				, otheruser__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::OtherUser)))
				, admin__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Admin)))
				, street__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Street)))
				, map__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Map)))
				, clearselection__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::ClearSelection)))
				, fontdecrease__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::FontDecrease)))
				, fontincrease__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::FontIncrease)))
				, fontsize__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::FontSize)))
				, cellphone__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::CellPhone)))
				, reshare__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::ReShare)))
				, tag__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Tag)))
				, repeatone__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::RepeatOne)))
				, repeatall__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::RepeatAll)))
				, outlinestar__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::OutlineStar)))
				, solidstar__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::SolidStar)))
				, calculator__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Calculator)))
				, directions__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Directions)))
				, target__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Target)))
				, library__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Library)))
				, phonebook__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::PhoneBook)))
				, memo__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Memo)))
				, microphone__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Microphone)))
				, postupdate__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::PostUpdate)))
				, backtowindow__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::BackToWindow)))
				, fullscreen__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::FullScreen)))
				, newfolder__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::NewFolder)))
				, calendarreply__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::CalendarReply)))
				, unsyncfolder__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::UnSyncFolder)))
				, reporthacked__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::ReportHacked)))
				, syncfolder__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::SyncFolder)))
				, blockcontact__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::BlockContact)))
				, switchapps__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::SwitchApps)))
				, addfriend__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::AddFriend)))
				, touchpointer__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::TouchPointer)))
				, gotostart__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::GoToStart)))
				, zerobars__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::ZeroBars)))
				, onebar__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::OneBar)))
				, twobars__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::TwoBars)))
				, threebars__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::ThreeBars)))
				, fourbars__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::FourBars)))
				, scan__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Scan)))
				, preview__(js_context.CreateNumber(static_cast<std::uint32_t>(Controls::Symbol::Preview)))
			{
				TITANIUM_LOG_DEBUG("SystemIcon::ctor Initialize");
			}

			void SystemIcon::postInitialize(JSObject& js_object)
			{
				TITANIUM_LOG_DEBUG("SystemIcon::postInitialize");
			}

			void SystemIcon::JSExportInitialize()
			{
				JSExport<SystemIcon>::SetClassVersion(1);
				JSExport<SystemIcon>::SetParent(JSExport<Titanium::Module>::Class());
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, PREVIOUS);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, NEXT);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, PLAY);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, PAUSE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, EDIT);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, SAVE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, CLEAR);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, DELETE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, REMOVE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, ADD);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, CANCEL);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, ACCEPT);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, MORE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, REDO);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, UNDO);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, HOME);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, UP);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, FORWARD);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, BACK);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, FAVORITE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, CAMERA);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, SETTING);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, VIDEO);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, SYNC);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, DOWNLOAD);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, MAIL);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, FIND);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, HELP);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, UPLOAD);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, EMOJI);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, TWOPAGE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, LEAVECHAT);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, MAILFORWARD);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, CLOCK);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, SEND);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, CROP);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, ROTATECAMERA);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, PEOPLE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, OPENPANE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, CLOSEPANE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, WORLD);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, FLAG);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, PREVIEWLINK);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, GLOBE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, TRIM);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, ATTACHCAMERA);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, ZOOMIN);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, BOOKMARKS);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, DOCUMENT);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, PROTECTEDDOCUMENT);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, PAGE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, BULLETS);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, COMMENT);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, MAILFILLED);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, CONTACTINFO);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, HANGUP);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, VIEWALL);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, MAPPIN);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, PHONE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, VIDEOCHAT);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, SWITCH);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, CONTACT);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, RENAME);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, PIN);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, MUSICINFO);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, GO);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, KEYBOARD);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, DOCKLEFT);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, DOCKRIGHT);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, DOCKBOTTOM);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, REMOTE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, REFRESH);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, ROTATE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, SHUFFLE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, LIST);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, SHOP);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, SELECTALL);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, ORIENTATION);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, IMPORT);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, IMPORTALL);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, BROWSEPHOTOS);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, WEBCAM);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, PICTURES);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, SAVELOCAL);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, CAPTION);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, STOP);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, SHOWRESULTS);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, VOLUME);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, REPAIR);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, MESSAGE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, PAGE2);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, CALENDARDAY);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, CALENDARWEEK);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, CALENDAR);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, CHARACTER);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, MAILREPLYALL);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, READ);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, LINK);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, ACCOUNT);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, SHOWBCC);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, HIDEBCC);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, CUT);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, ATTACH);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, PASTE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, FILTER);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, COPY);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, EMOJI2);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, IMPORTANT);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, MAILREPLY);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, SLIDESHOW);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, SORT);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, MANAGE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, ALLAPPS);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, DISCONNECTDRIVE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, MAPDRIVE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, NEWWINDOW);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, OPENWITH);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, CONTACTPRESENCE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, PRIORITY);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, GOTOTODAY);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, FONT);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, FONTCOLOR);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, CONTACT2);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, FOLDER);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, AUDIO);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, PLACEHOLDER);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, VIEW);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, SETLOCKSCREEN);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, SETTILE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, CLOSEDCAPTION);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, STOPSLIDESHOW);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, PERMISSIONS);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, HIGHLIGHT);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, DISABLEUPDATES);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, UNFAVORITE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, UNPIN);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, OPENLOCAL);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, MUTE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, ITALIC);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, UNDERLINE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, BOLD);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, MOVETOFOLDER);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, LIKEDISLIKE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, DISLIKE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, LIKE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, ALIGNRIGHT);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, ALIGNCENTER);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, ALIGNLEFT);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, ZOOM);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, ZOOMOUT);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, OPENFILE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, OTHERUSER);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, ADMIN);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, STREET);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, MAP);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, CLEARSELECTION);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, FONTDECREASE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, FONTINCREASE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, FONTSIZE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, CELLPHONE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, RESHARE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, TAG);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, REPEATONE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, REPEATALL);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, OUTLINESTAR);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, SOLIDSTAR);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, CALCULATOR);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, DIRECTIONS);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, TARGET);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, LIBRARY);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, PHONEBOOK);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, MEMO);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, MICROPHONE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, POSTUPDATE);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, BACKTOWINDOW);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, FULLSCREEN);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, NEWFOLDER);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, CALENDARREPLY);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, UNSYNCFOLDER);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, REPORTHACKED);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, SYNCFOLDER);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, BLOCKCONTACT);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, SWITCHAPPS);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, ADDFRIEND);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, TOUCHPOINTER);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, GOTOSTART);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, ZEROBARS);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, ONEBAR);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, TWOBARS);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, THREEBARS);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, FOURBARS);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, SCAN);
				TITANIUM_ADD_PROPERTY_READONLY(SystemIcon, PREVIEW);
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, PREVIOUS)
			{
				return previous__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, NEXT)
			{
				return next__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, PLAY)
			{
				return play__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, PAUSE)
			{
				return pause__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, EDIT)
			{
				return edit__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, SAVE)
			{
				return save__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, CLEAR)
			{
				return clear__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, DELETE)
			{
				return delete__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, REMOVE)
			{
				return remove__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, ADD)
			{
				return add__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, CANCEL)
			{
				return cancel__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, ACCEPT)
			{
				return accept__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, MORE)
			{
				return more__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, REDO)
			{
				return redo__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, UNDO)
			{
				return undo__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, HOME)
			{
				return home__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, UP)
			{
				return up__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, FORWARD)
			{
				return forward__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, BACK)
			{
				return back__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, FAVORITE)
			{
				return favorite__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, CAMERA)
			{
				return camera__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, SETTING)
			{
				return setting__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, VIDEO)
			{
				return video__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, SYNC)
			{
				return sync__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, DOWNLOAD)
			{
				return download__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, MAIL)
			{
				return mail__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, FIND)
			{
				return find__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, HELP)
			{
				return help__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, UPLOAD)
			{
				return upload__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, EMOJI)
			{
				return emoji__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, TWOPAGE)
			{
				return twopage__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, LEAVECHAT)
			{
				return leavechat__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, MAILFORWARD)
			{
				return mailforward__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, CLOCK)
			{
				return clock__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, SEND)
			{
				return send__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, CROP)
			{
				return crop__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, ROTATECAMERA)
			{
				return rotatecamera__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, PEOPLE)
			{
				return people__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, OPENPANE)
			{
				return openpane__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, CLOSEPANE)
			{
				return closepane__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, WORLD)
			{
				return world__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, FLAG)
			{
				return flag__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, PREVIEWLINK)
			{
				return previewlink__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, GLOBE)
			{
				return globe__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, TRIM)
			{
				return trim__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, ATTACHCAMERA)
			{
				return attachcamera__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, ZOOMIN)
			{
				return zoomin__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, BOOKMARKS)
			{
				return bookmarks__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, DOCUMENT)
			{
				return document__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, PROTECTEDDOCUMENT)
			{
				return protecteddocument__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, PAGE)
			{
				return page__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, BULLETS)
			{
				return bullets__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, COMMENT)
			{
				return comment__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, MAILFILLED)
			{
				return mailfilled__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, CONTACTINFO)
			{
				return contactinfo__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, HANGUP)
			{
				return hangup__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, VIEWALL)
			{
				return viewall__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, MAPPIN)
			{
				return mappin__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, PHONE)
			{
				return phone__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, VIDEOCHAT)
			{
				return videochat__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, SWITCH)
			{
				return switch__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, CONTACT)
			{
				return contact__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, RENAME)
			{
				return rename__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, PIN)
			{
				return pin__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, MUSICINFO)
			{
				return musicinfo__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, GO)
			{
				return go__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, KEYBOARD)
			{
				return keyboard__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, DOCKLEFT)
			{
				return dockleft__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, DOCKRIGHT)
			{
				return dockright__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, DOCKBOTTOM)
			{
				return dockbottom__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, REMOTE)
			{
				return remote__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, REFRESH)
			{
				return refresh__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, ROTATE)
			{
				return rotate__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, SHUFFLE)
			{
				return shuffle__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, LIST)
			{
				return list__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, SHOP)
			{
				return shop__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, SELECTALL)
			{
				return selectall__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, ORIENTATION)
			{
				return orientation__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, IMPORT)
			{
				return import__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, IMPORTALL)
			{
				return importall__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, BROWSEPHOTOS)
			{
				return browsephotos__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, WEBCAM)
			{
				return webcam__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, PICTURES)
			{
				return pictures__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, SAVELOCAL)
			{
				return savelocal__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, CAPTION)
			{
				return caption__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, STOP)
			{
				return stop__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, SHOWRESULTS)
			{
				return showresults__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, VOLUME)
			{
				return volume__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, REPAIR)
			{
				return repair__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, MESSAGE)
			{
				return message__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, PAGE2)
			{
				return page2__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, CALENDARDAY)
			{
				return calendarday__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, CALENDARWEEK)
			{
				return calendarweek__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, CALENDAR)
			{
				return calendar__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, CHARACTER)
			{
				return character__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, MAILREPLYALL)
			{
				return mailreplyall__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, READ)
			{
				return read__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, LINK)
			{
				return link__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, ACCOUNT)
			{
				return account__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, SHOWBCC)
			{
				return showbcc__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, HIDEBCC)
			{
				return hidebcc__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, CUT)
			{
				return cut__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, ATTACH)
			{
				return attach__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, PASTE)
			{
				return paste__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, FILTER)
			{
				return filter__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, COPY)
			{
				return copy__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, EMOJI2)
			{
				return emoji2__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, IMPORTANT)
			{
				return important__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, MAILREPLY)
			{
				return mailreply__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, SLIDESHOW)
			{
				return slideshow__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, SORT)
			{
				return sort__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, MANAGE)
			{
				return manage__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, ALLAPPS)
			{
				return allapps__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, DISCONNECTDRIVE)
			{
				return disconnectdrive__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, MAPDRIVE)
			{
				return mapdrive__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, NEWWINDOW)
			{
				return newwindow__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, OPENWITH)
			{
				return openwith__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, CONTACTPRESENCE)
			{
				return contactpresence__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, PRIORITY)
			{
				return priority__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, GOTOTODAY)
			{
				return gototoday__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, FONT)
			{
				return font__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, FONTCOLOR)
			{
				return fontcolor__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, CONTACT2)
			{
				return contact2__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, FOLDER)
			{
				return folder__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, AUDIO)
			{
				return audio__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, PLACEHOLDER)
			{
				return placeholder__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, VIEW)
			{
				return view__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, SETLOCKSCREEN)
			{
				return setlockscreen__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, SETTILE)
			{
				return settile__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, CLOSEDCAPTION)
			{
				return closedcaption__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, STOPSLIDESHOW)
			{
				return stopslideshow__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, PERMISSIONS)
			{
				return permissions__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, HIGHLIGHT)
			{
				return highlight__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, DISABLEUPDATES)
			{
				return disableupdates__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, UNFAVORITE)
			{
				return unfavorite__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, UNPIN)
			{
				return unpin__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, OPENLOCAL)
			{
				return openlocal__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, MUTE)
			{
				return mute__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, ITALIC)
			{
				return italic__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, UNDERLINE)
			{
				return underline__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, BOLD)
			{
				return bold__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, MOVETOFOLDER)
			{
				return movetofolder__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, LIKEDISLIKE)
			{
				return likedislike__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, DISLIKE)
			{
				return dislike__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, LIKE)
			{
				return like__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, ALIGNRIGHT)
			{
				return alignright__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, ALIGNCENTER)
			{
				return aligncenter__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, ALIGNLEFT)
			{
				return alignleft__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, ZOOM)
			{
				return zoom__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, ZOOMOUT)
			{
				return zoomout__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, OPENFILE)
			{
				return openfile__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, OTHERUSER)
			{
				return otheruser__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, ADMIN)
			{
				return admin__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, STREET)
			{
				return street__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, MAP)
			{
				return map__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, CLEARSELECTION)
			{
				return clearselection__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, FONTDECREASE)
			{
				return fontdecrease__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, FONTINCREASE)
			{
				return fontincrease__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, FONTSIZE)
			{
				return fontsize__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, CELLPHONE)
			{
				return cellphone__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, RESHARE)
			{
				return reshare__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, TAG)
			{
				return tag__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, REPEATONE)
			{
				return repeatone__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, REPEATALL)
			{
				return repeatall__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, OUTLINESTAR)
			{
				return outlinestar__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, SOLIDSTAR)
			{
				return solidstar__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, CALCULATOR)
			{
				return calculator__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, DIRECTIONS)
			{
				return directions__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, TARGET)
			{
				return target__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, LIBRARY)
			{
				return library__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, PHONEBOOK)
			{
				return phonebook__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, MEMO)
			{
				return memo__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, MICROPHONE)
			{
				return microphone__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, POSTUPDATE)
			{
				return postupdate__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, BACKTOWINDOW)
			{
				return backtowindow__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, FULLSCREEN)
			{
				return fullscreen__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, NEWFOLDER)
			{
				return newfolder__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, CALENDARREPLY)
			{
				return calendarreply__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, UNSYNCFOLDER)
			{
				return unsyncfolder__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, REPORTHACKED)
			{
				return reporthacked__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, SYNCFOLDER)
			{
				return syncfolder__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, BLOCKCONTACT)
			{
				return blockcontact__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, SWITCHAPPS)
			{
				return switchapps__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, ADDFRIEND)
			{
				return addfriend__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, TOUCHPOINTER)
			{
				return touchpointer__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, GOTOSTART)
			{
				return gotostart__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, ZEROBARS)
			{
				return zerobars__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, ONEBAR)
			{
				return onebar__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, TWOBARS)
			{
				return twobars__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, THREEBARS)
			{
				return threebars__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, FOURBARS)
			{
				return fourbars__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, SCAN)
			{
				return scan__;
			}

			TITANIUM_PROPERTY_GETTER(SystemIcon, PREVIEW)
			{
				return preview__;
			}

		}  // namespace WindowsXaml
	}  // namespace UI
}  // namespace TitaniumWindows
