// Copyright (c) 2021 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=f54014218a54c7925d85df2f162fd51962dac2ce$
//

#ifndef CEF_LIBCEF_DLL_CTOCPP_REQUEST_CONTEXT_CTOCPP_H_
#define CEF_LIBCEF_DLL_CTOCPP_REQUEST_CONTEXT_CTOCPP_H_
#pragma once

#if !defined(WRAPPING_CEF_SHARED)
#error This file can be included wrapper-side only
#endif

#include <vector>
#include "include/capi/cef_request_context_capi.h"
#include "include/capi/cef_request_context_handler_capi.h"
#include "include/capi/cef_scheme_capi.h"
#include "include/cef_request_context.h"
#include "include/cef_request_context_handler.h"
#include "include/cef_scheme.h"
#include "libcef_dll/ctocpp/ctocpp_ref_counted.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed wrapper-side only.
class CefRequestContextCToCpp
    : public CefCToCppRefCounted<CefRequestContextCToCpp,
                                 CefRequestContext,
                                 cef_request_context_t> {
 public:
  CefRequestContextCToCpp();
  virtual ~CefRequestContextCToCpp();

  // CefRequestContext methods.
  bool IsSame(CefRefPtr<CefRequestContext> other) OVERRIDE;
  bool IsSharingWith(CefRefPtr<CefRequestContext> other) OVERRIDE;
  bool IsGlobal() OVERRIDE;
  CefRefPtr<CefRequestContextHandler> GetHandler() OVERRIDE;
  CefString GetCachePath() OVERRIDE;
  CefRefPtr<CefCookieManager> GetCookieManager(
      CefRefPtr<CefCompletionCallback> callback) OVERRIDE;
  bool RegisterSchemeHandlerFactory(
      const CefString& scheme_name,
      const CefString& domain_name,
      CefRefPtr<CefSchemeHandlerFactory> factory) OVERRIDE;
  bool ClearSchemeHandlerFactories() OVERRIDE;
  void PurgePluginListCache(bool reload_pages) OVERRIDE;
  bool HasPreference(const CefString& name) OVERRIDE;
  CefRefPtr<CefValue> GetPreference(const CefString& name) OVERRIDE;
  CefRefPtr<CefDictionaryValue> GetAllPreferences(
      bool include_defaults) OVERRIDE;
  bool CanSetPreference(const CefString& name) OVERRIDE;
  bool SetPreference(const CefString& name,
                     CefRefPtr<CefValue> value,
                     CefString& error) OVERRIDE;
  void ClearCertificateExceptions(
      CefRefPtr<CefCompletionCallback> callback) OVERRIDE;
  void ClearHttpAuthCredentials(
      CefRefPtr<CefCompletionCallback> callback) OVERRIDE;
  void CloseAllConnections(CefRefPtr<CefCompletionCallback> callback) OVERRIDE;
  void ResolveHost(const CefString& origin,
                   CefRefPtr<CefResolveCallback> callback) OVERRIDE;
  void LoadExtension(const CefString& root_directory,
                     CefRefPtr<CefDictionaryValue> manifest,
                     CefRefPtr<CefExtensionHandler> handler) OVERRIDE;
  bool DidLoadExtension(const CefString& extension_id) OVERRIDE;
  bool HasExtension(const CefString& extension_id) OVERRIDE;
  bool GetExtensions(std::vector<CefString>& extension_ids) OVERRIDE;
  CefRefPtr<CefExtension> GetExtension(const CefString& extension_id) OVERRIDE;
  CefRefPtr<CefMediaRouter> GetMediaRouter() OVERRIDE;
};

#endif  // CEF_LIBCEF_DLL_CTOCPP_REQUEST_CONTEXT_CTOCPP_H_
