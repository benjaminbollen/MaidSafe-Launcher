/*  Copyright 2014 MaidSafe.net limited

    This MaidSafe Software is licensed to you under (1) the MaidSafe.net Commercial License,
    version 1.0 or later, or (2) The General Public License (GPL), version 3, depending on which
    licence you accepted on initial access to the Software (the "Licences").

    By contributing code to the MaidSafe Software, or to this project generally, you agree to be
    bound by the terms of the MaidSafe Contributor Agreement, version 1.0, found in the root
    directory of this project at LICENSE, COPYING and CONTRIBUTOR respectively and also
    available at: http://www.maidsafe.net/licenses

    Unless required by applicable law or agreed to in writing, the MaidSafe Software distributed
    under the GPL Licence is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS
    OF ANY KIND, either express or implied.

    See the Licences for the specific language governing permissions and limitations relating to
    use of the MaidSafe Software.                                                                 */

#ifndef MAIDSAFE_LAUNCHER_ACCOUNT_HANDLER_H_
#define MAIDSAFE_LAUNCHER_ACCOUNT_HANDLER_H_

#include <memory>

#include "maidsafe/common/config.h"
#include "maidsafe/common/types.h"
#include "maidsafe/common/authentication/user_credentials.h"
#include "maidsafe/common/data_types/structured_data_versions.h"

#include "maidsafe/launcher/account.h"
#include "maidsafe/launcher/types.h"

namespace maidsafe {

namespace launcher {

class AccountGetter;

// This class is not threadsafe.
class AccountHandler {
 public:
  // This constructor should be used before logging in to an existing account, i.e. where the
  // account has not yet been retrieved from the network.  Throws on error.
  AccountHandler();

  // This constructor should be used when creating a new account, i.e. where a account has never
  // been put to the network.  'network_client' should already be joined to the network.  Internally
  // saves the first account after creating the new account.  Throws on error.
  AccountHandler(Account&& account, authentication::UserCredentials&& user_credentials,
                 NetworkClient& network_client);

  AccountHandler(const AccountHandler&) = delete;
  AccountHandler(AccountHandler&& other) = delete;
  AccountHandler& operator=(const AccountHandler&) = delete;
  AccountHandler& operator=(AccountHandler&& other) = delete;

  // Retrieves and decrypts account info when logging in to an existing account.  'account_getter'
  // should already be joined to the network.  Throws on error, including already having logged in.
  // Provides strong exception guarantee.
  void Login(authentication::UserCredentials&& user_credentials, AccountGetter& account_getter);

  // Saves account on the network using 'network_client', which should already be joined to the
  // network.  Throws on error, with strong exception guarantee.
  void Save(NetworkClient& network_client);

  // Give full access to the account
  std::unique_ptr<Account> account_;

 private:
  StructuredDataVersions account_versions_;
  authentication::UserCredentials user_credentials_;
};

}  // namespace launcher

}  // namespace maidsafe

#endif  // MAIDSAFE_LAUNCHER_ACCOUNT_HANDLER_H_
