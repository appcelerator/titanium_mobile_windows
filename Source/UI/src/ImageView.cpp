/**
* Titanium.UI.ImageView for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/UI/ImageView.hpp"
#include "LayoutEngine/LayoutEngine.hpp"


namespace TitaniumWindows { namespace UI {

  ImageView::ImageView(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Titanium::UI::ImageView(js_context)
    , image__(ref new Windows::UI::Xaml::Controls::Image())  {
    TITANIUM_LOG_DEBUG("ImageView::ctor Initialize");
  }

  ImageView::ImageView(const ImageView& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Titanium::UI::ImageView(rhs, arguments)
    , image__(ref new Windows::UI::Xaml::Controls::Image())  {
    using namespace Windows::UI::Xaml;
    using namespace Windows::UI::Xaml::Controls;

    setComponent(image__);

    internal_load_event_ = image__->ImageOpened += ref new RoutedEventHandler([this](::Platform::Object ^sender, RoutedEventArgs ^e) {
      auto rect = Titanium::LayoutEngine::RectMake(
        Canvas::GetLeft(this->image__),
        Canvas::GetTop(this->image__),
        this->image__->ActualWidth,
        this->image__->ActualHeight
        );
      this->onComponentSizeChange(rect);
    });

    TITANIUM_LOG_DEBUG("ImageView::ctor CallAsConstructor");
  }

  void ImageView::JSExportInitialize() {
    JSExport<ImageView>::SetClassVersion(1);
    JSExport<ImageView>::SetParent(JSExport<Titanium::UI::ImageView>::Class());
  }

  bool ImageView::setImageArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString());
    std::string path = static_cast<std::string>(argument);
    path_ = path;
    // if the path isn't an http/s URI already, fix URI to point to local files in app
    if (!boost::starts_with(path, "http://") && !boost::starts_with(path, "https://")) {
      // URIs must be absolute
      if (!boost::starts_with(path, "/")) {
        path = "/" + path;
      }
      // use MS's in-app URL scheme
      path = "ms-appx://" + path;
    }
    auto uri = ref new Windows::Foundation::Uri(ref new Platform::String(std::wstring(path.begin(), path.end()).c_str()));
    auto image = ref new Windows::UI::Xaml::Media::Imaging::BitmapImage(uri);
    image__->Source = image;
    TITANIUM_LOG_DEBUG("ImageView::setImageArgumentValidator: image = ", path);
    set_image(argument);
    return true;
  }

  bool ImageView::setTopArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    bool result = false;
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("ImageView::setTopArgumentValidator: top = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Top, static_cast<std::string>(argument));
    set_top(argument);
    result = true;
    return result;
  }

  bool ImageView::setLeftArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    bool result = false;
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("ImageView::setLeftArgumentValidator: left = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Left, static_cast<std::string>(argument));
    set_left(argument);
    result = true;
    return result;
  }

  bool ImageView::setWidthArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    bool result = false;
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("ImageView::setWidthArgumentValidator: width = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Width, static_cast<std::string>(argument));
    set_width(argument);
    result = true;
    return result;
  }

    bool ImageView::setHeightArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    bool result = false;
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("ImageView::setHeightArgumentValidator: height = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Height, static_cast<std::string>(argument));
    set_height(argument);
    result = true;
    return result;
  }

  void ImageView::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_DEBUG("ImageView::enableEvent: (event name '", event_name, "'");

    const JSContext  ctx = this->get_context();

    using namespace Windows::UI::Xaml::Input;
    using namespace Windows::UI::Xaml;

    if (event_name == "click") {
      if (click_event_count_ == 0) {
        click_event_ = getComponent()->Tapped += ref new TappedEventHandler([this, ctx](::Platform::Object ^ sender, TappedRoutedEventArgs ^ e) {
          auto component = safe_cast<FrameworkElement^>(sender);
          auto position = e->GetPosition(component);

          JSObject  eventArgs = ctx.CreateObject();
          eventArgs.SetProperty("x", ctx.CreateNumber(position.X));
          eventArgs.SetProperty("y", ctx.CreateNumber(position.Y));

          this->fireEvent("click", eventArgs);
        });
      }

      ++click_event_count_;

      return;
    }
  }

}} // namespace TitaniumWindows { namespace UI {

